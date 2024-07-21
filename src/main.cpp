/**
 * @file main.cpp
 * @brief Main file for MySimRacingCore project.
 */

#include <Arduino.h>



#include "Core/ComUsb.hpp"
#include "Core/Buttons.hpp"
#include "Core/Encoder.hpp"
#include "Core/Joyst.hpp"
#ifndef LUSMDL_DEBUGMODE
#include "Core/SetupDisplay.hpp"
#endif
    
#include <EEPROM.h>


    
void encoderHandleInterrupt();

Buttons buttons(Wire);
Encoder encoder;
Joyst joy;

#ifndef LUSMDL_DEBUGMODE
SetupDisplay display(joy, encoder, EEPROM);
#endif

ComUsb com(buttons, joy, encoder);

bool runSetup {1}; // save if a setup is running

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
    display.begin();
    encoder.begin();
    #endif

    buttons.begin();
    joy.rotationX_.begin();
    joy.rotationY_.begin();
    joy.beginButton();
    
    encoder.begin();

    com.begin();
}

/**
 * @brief Arduino loop function.
 * 
 * This function is called repeatedly in an infinite loop.
 */
void loop() {

    _delay_ms(1);
    
    #ifdef LUSMDL_DEBUGMODE
    Serial.print("\n\n------------------------------------------------------------------\n");
    _delay_ms(100);
    #endif

    #ifndef LUSMDL_DEBUGMODE
    if (runSetup) {

        runSetup = display.runSetup();
    }
    #endif

    buttons.listener();

    joy.rotationX_.updateRawData();
    joy.rotationY_.updateRawData();


    com.sendData();
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
