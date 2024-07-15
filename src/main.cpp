/**
 * @file main.cpp
 * @brief Main file for MySimRacingCore project.
 */

#include <Arduino.h>



#include "Core/ComUsb.hpp"
#include "Core/Buttons.hpp"
#include "Core/Encoder.hpp"
#include "Core/Joyst.hpp"
#ifndef LSMDL_DEBUGMODE
#include "Core/SetupDisplay.hpp"
#endif
    
    
void encoderHandleInterrupt();

Buttons buttons(Wire);
Encoder encoder;
Joyst joy;

#ifndef LSMDL_DEBUGMODE
SetupDisplay display;
#endif

ComUsb com(buttons, joy);

/**
 * @brief Arduino setup function.
 * 
 * This function is called once when the Arduino starts.
 */
void setup() {

    #ifdef LSMDL_DEBUGMODE
    Serial.begin(9600);
    #endif

    #ifndef LSMDL_DEBUGMODE
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

    _delay_ms(1);

    buttons.listener();

    joy.rotationX_.updateRawData();
    joy.rotationY_.updateRawData();

    #ifdef LSMDL_DEBUGMODE
    joy_.rotationX_.getData();
    joy_.rotationY_.getData();
    _delay_ms(100);
    #endif

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
