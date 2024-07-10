#include "ComUsb.hpp"

ComUsb::ComUsb(Buttons &btns) :
    btns_(&btns),
    joy_(
        JOYSTICK_DEFAULT_REPORT_ID, // REPORT_ID        Hid report id
        JOYSTICK_TYPE_MULTI_AXIS, // JOYSTICK_TYPE      Type of device: JOYSTICK, GAMEPAD, MULTI_AXIS
        BTN_NUMBER, // button count                     [0-32]
        0, // Hat Switch count                          [0,1,2]
        true, // X Axis enable                          True or False
        false, // Y Axis enable                         True or False
        true, // Z Axis enable                          True or False
        true, // Rx Axis enable                         True or False
        true, // Ry Axis enable                         True or False
        false, // Rz Axis enable                        True or False
        false, // Rudder enable                         True or False
        false, // Throttle enable                       True or False
        true, // Accelerator enable                     True or False
        true, // Brake enable                           True or False
        false // Steering enable                        True or False
        )
    {}

ComUsb::~ComUsb() {}

void ComUsb::begin() {

    // Initialization code for USB communication

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

    joy_.begin(false); // sendState() method is nessesarry if (false)
}

void ComUsb::sendData() {

    // Code to send data via USB

    for (uint8_t i = 0; i < BTN_NUMBER; i++) {

        joy_.setButton(i, btns_->data_[i].pushed);
    }


    joy_.sendState();

    /*
    joy_.pressButton(12);
    joy_.sendState();
    _delay_ms(1000);
    joy_.releaseButton(12);
    joy_.sendState();
    _delay_ms(1000);
    */
    
}
