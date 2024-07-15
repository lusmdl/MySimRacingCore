/**
 * @file MySimRacingCore.cpp
 * @brief Implementation of the MySimRacingCore class.
 */

#include "MySimRacingCore.hpp"

/**
 * @brief Constructor for MySimRacingCore class.
 * 
 * Initializes the ComUsb object with the Buttons object.
 */
MySimRacingCore::MySimRacingCore() :
    com_(buttons_, joy_)
{}

/**
 * @brief Sets up the MySimRacingCore components.
 * 
 * Initializes the serial communication if LSMDL_DEBUGMODE is defined.
 * Calls the begin method of Buttons and ComUsb objects.
 */
void MySimRacingCore::setup() {
    
    #ifdef LSMDL_DEBUGMODE
    Serial.begin(9600);
    #endif

    display_.begin();

    buttons_.begin();
    joy_.rotationX_.begin();
    joy_.rotationY_.begin();
    joy_.beginButton();

    

    com_.begin();
}

/**
 * @brief Main loop function for MySimRacingCore.
 * 
 * Calls the listener method of Buttons object and sendData method of ComUsb object.
 * Adds a delay of 1 millisecond.
 */
void MySimRacingCore::loop() {
    _delay_ms(1);

    buttons_.listener();

    joy_.rotationX_.updateRawData();

    #ifdef LSMDL_DEBUGMODE
    joy_.rotationX_.getData();
    #endif

    joy_.rotationY_.updateRawData();

    #ifdef LSMDL_DEBUGMODE
    joy_.rotationY_.getData();
    #endif

    com_.sendData();
}

/**
 * @brief Handles encoder interrupts.
 * 
 * Calls the handleInterrupt method of the Encoder object.
 */
void MySimRacingCore::encoderHandleInterrupt() {

    encoder_.handleInterrupt();
}
