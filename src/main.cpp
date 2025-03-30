/**
 * @file main.cpp
 * @brief Main file for MySimRacingCore project.
 */


// libs

#include <Arduino.h>
#include <EEPROM.h>


// include macros

#include "ProjectConfig.hpp"
#include "DigitalWriteFast.h"
#include "EepromAdresses.h"


// source code modules

#include "Core/ComUsb.hpp"
#include "Core/Buttons.hpp"
#include "Core/Encoder.hpp"
#include "Core/Joyst.hpp"
#include "Core/Pedals.hpp"
#include "Core/SetupDisplay.hpp"


// objects

Buttons buttons(Wire);
Encoder encoder(ENCODER_A_PIN, ENCODER_B_PIN);
Joyst joy;
Pedals pedal;
SetupDisplay display(joy, pedal, encoder, EEPROM, Wire);
ComUsb com(buttons, joy, pedal, encoder);


// declaration of global variables

uint8_t runSetup            {1}; // store the state, if a setup is running
unsigned int numberOfCycle  {0}; // count the cycles


// forward declaration of public functions

void loopFast();
void loopNormal();
void loopSlow();
void handleInterrupt();


/**
 * @brief Arduino setup function.
 * 
 * This function is called once when the Arduino starts.
 */
void setup() {
    
    
    #ifdef LUSMDL_DEBUGMODE
    Serial.begin(9600);
    #endif
    
    #ifndef LUSMDL_DEBUGMODE 
    attachInterrupt(digitalPinToInterrupt(encoder.pinA_), handleInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder.pinB_), handleInterrupt, CHANGE);
    #endif
    
    EEPROM.begin();
    Wire.begin();
    display.begin();
    joy.beginButton();
    joy.rotationX_.begin();
    joy.rotationY_.begin();
    pedal.brake_.begin();
    pedal.throttle_.begin();
    com.begin();
    
}


/**
 * @brief Arduino loop function.
 * 
 * This function is called repeatedly in an infinite loop.
 */
void loop() {


    numberOfCycle++;

    if((numberOfCycle % TIME_FAST) == 0) {

        // here are task which has priority

        loopFast();
    }
    
    if((numberOfCycle % TIME_NORMAL) == 0) {

        // here are task which has no priority

        loopNormal();
    }
    
    if((numberOfCycle % TIME_SLOW) == 0) {

        // here are tasks which slow down the code

        loopSlow();
    }

    #ifdef LUSMDL_DEBUGMODE
    Serial.print("\n\n------------------------------------------------------------------\n");
    _delay_ms(100);
    #endif
}

void loopFast() {

    // send USB Game data

    com.sendData();
}

void loopNormal() {

    // read analog Axis
    
    joy.rotationX_.updateRawData();
    joy.rotationY_.updateRawData();
    
    pedal.throttle_.updateRawData();
    pedal.brake_.updateRawData();
}

void loopSlow() {

    // read buttons over I²C

    buttons.listener();

    #ifndef LUSMDL_DEBUGMODE
    display.runSetup();
    #endif
}


//ISR

ISR(TIMER3_COMPA_vect){
    
    // receive USB Game data
    
    com.receiveData();
}


void handleInterrupt(void) {
    
    int sig1 = digitalReadFast(encoder.pinA_);
    int sig2 = digitalReadFast(encoder.pinB_);
    int8_t thisState = sig1 | (sig2 << 1);

    if (encoder.oldState_ != thisState) {
        encoder.position_ += encoder.KNOBDIR[thisState | (encoder.oldState_ << 2)];
        encoder.oldState_ = thisState;
    }
}