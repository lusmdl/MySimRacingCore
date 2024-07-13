/**
 * @file main.cpp
 * @brief Main file for MySimRacingCore project.
 */

#include <Arduino.h>
#include "MySimRacingCore/MySimRacingCore.hpp"

MySimRacingCore core;

/**
 * @brief Arduino setup function.
 * 
 * This function is called once when the Arduino starts.
 */
void setup() {

    core.setup();
}

/**
 * @brief Arduino loop function.
 * 
 * This function is called repeatedly in an infinite loop.
 */
void loop() {

    core.loop();
}

/**
 * @brief Interrupt Service Routine for INT0.
 * 
 * This ISR is triggered by events on the INT0 pin (external interrupt 0).
 */
ISR(INT0_vect) {

    core.encoderHandleInterrupt();
}

/**
 * @brief Interrupt Service Routine for INT1.
 * 
 * This ISR is triggered by events on the INT1 pin (external interrupt 1).
 */
ISR(INT1_vect) {
    
    core.encoderHandleInterrupt();
}
