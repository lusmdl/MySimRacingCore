/**
 * @file ComUsb.cpp
 * @brief Implementation of the ComUsb class.
 */

#include "ComUsb.hpp"

/**
 * @brief Constructor for ComUsb class.
 * 
 * Initializes the joystick and sets the button reference.
 * 
 * @param btns Reference to the Buttons object.
 */
ComUsb::ComUsb(Buttons &btns) :
    btns_(&btns),
    joy_(
        JOYSTICK_DEFAULT_REPORT_ID, // REPORT_ID        Hid report id
        JOYSTICK_TYPE_MULTI_AXIS,   // JOYSTICK_TYPE    Type of device: JOYSTICK, GAMEPAD, MULTI_AXIS
        BTN_NUMBER,                 // button count     [0-32]
        0,                          // Hat Switch count [0,1,2]
        true,                       // X Axis enable    True or False
        false,                      // Y Axis enable    True or False
        true,                       // Z Axis enable    True or False
        true,                       // Rx Axis enable   True or False
        true,                       // Ry Axis enable   True or False
        false,                      // Rz Axis enable   True or False
        false,                      // Rudder enable    True or False
        false,                      // Throttle enable  True or False
        true,                       // Accelerator enable True or False
        true,                       // Brake enable     True or False
        false                       // Steering enable  True or False
    )
{}

/**
 * @brief Destructor for ComUsb class.
 */
ComUsb::~ComUsb() {}

/**
 * @brief Initializes the USB communication.
 * 
 * Sets the range for joystick axes and begins the joystick interface.
 */
void ComUsb::begin() {
    
    joy_.setXAxisRange(-32768, 32767);
    //joy_.setYAxisRange(-32768, 32767);
    joy_.setZAxisRange(-32768, 32767);
    joy_.setRxAxisRange(-32768, 32767);
    joy_.setRyAxisRange(-32768, 32767);
    //joy_.setRzAxisRange(-32768, 32767);
    //joy_.setRudderRange(-32768, 32767);
    //joy_.setThrottleRange(-32768, 32767);
    joy_.setAcceleratorRange(-32768, 32767);
    joy_.setBrakeRange(-32768, 32767);
    //joy_.setSteeringRange(-32768, 32767);

    joy_.begin(false); // sendState() method is necessary if (false)
}

/**
 * @brief Sends data via USB.
 * 
 * Reads the button states from the Buttons object and updates the joystick interface.
 */
void ComUsb::sendData() {

    for (uint8_t i = 0; i < BTN_NUMBER; i++) {

        joy_.setButton(i, btns_->getData(i).pushed);
    }
    joy_.sendState();
}
