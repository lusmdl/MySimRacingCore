/**
 * @file main.cpp
 * @brief Main file for MySimRacingCore project.
 */

// libs

#include <Arduino.h>

// source code modules

#include "Core/ComUsb.hpp"
#include "Core/Buttons.hpp"
#include "Core/Encoder.hpp"
#include "Core/Joyst.hpp"
#include "Core/Pedals.hpp"
#ifndef LUSMDL_DEBUGMODE
#include "Core/SetupDisplay.hpp"
#endif

// objects

Buttons buttons(Wire);
Encoder encoder;
Joyst joy;
Pedals pedal;
#ifndef LUSMDL_DEBUGMODE
SetupDisplay display(joy, pedal, encoder, EEPROM);
#endif
ComUsb com(buttons, joy, pedal, encoder);

// declaration of global variables

bool runSetup               {1}; // save if a setup is running
unsigned int numberOfCycle {0}; // count the cycles

// forward declaration of public functions

void encoderHandleInterrupt();
void loopFast();
void loopNormal();
void loopSlow();

/**
 * @brief Arduino setup function.
 * 
 * This function is called once when the Arduino starts.
 */
void setup() {
    
    EEPROM.begin();

    #ifdef LUSMDL_DEBUGMODE
    Serial.begin(9600);
    #endif

    #ifndef LUSMDL_DEBUGMODE
    encoder.begin(); // encoder pins are stolen by the uart
    display.begin();
    #endif

    buttons.begin();

    joy.rotationX_.begin();
    joy.rotationY_.begin();
    joy.beginButton();

    com.begin();
}

/**
 * @brief Arduino loop function.
 * 
 * This function is called repeatedly in an infinite loop.
 */
void loop() {

    static const unsigned int TIME_FAST     = 3;
    static const unsigned int TIME_NORMAL   = 50;
    static const unsigned int TIME_SLOW     = 1000;
    
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

/**
 * @brief Interrupt Service Routine for INT0.
 * 
 * This ISR is triggered by events on the INT0 pin (external interrupt 0).
 */
ISR(INT0_vect) {

    encoder.handleInterrupt();
}

/**
 * @brief Interrupt Service Routine for INT1.
 * 
 * This ISR is triggered by events on the INT1 pin (external interrupt 1).
 */
ISR(INT1_vect) {
    
    encoder.handleInterrupt();
}

void loopFast() {

    // read analog Axis

    joy.rotationX_.updateRawData();
    joy.rotationY_.updateRawData();

    pedal.throttle_.updateRawData();
    pedal.brake_.updateRawData();
    
    // send USB Game data

    com.sendData();
}

void loopNormal() {

    // receive USB Game data

    com.receiveData();

    // read buttons over I²C

    buttons.listener();
}

void loopSlow() {

    #ifndef LUSMDL_DEBUGMODE
    if (runSetup) {

        runSetup = display.runSetup();
    }
    else {

        display.showSteering();
    }
    #endif
}