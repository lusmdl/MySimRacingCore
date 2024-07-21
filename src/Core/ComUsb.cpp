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
ComUsb::ComUsb(Buttons &btns, Joyst &joyst, Encoder &encoder) :
    btns_(&btns),
    joyst_(&joyst),
    encoder_(&encoder),
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
    
    joy_.setXAxisRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    //joy_.setYAxisRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    joy_.setZAxisRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    joy_.setRxAxisRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    joy_.setRyAxisRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    //joy_.setRzAxisRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    //joy_.setRudderRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    //joy_.setThrottleRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    joy_.setAcceleratorRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    joy_.setBrakeRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);
    //joy_.setSteeringRange(MIN_AXIS_VALUE, MAX_AXIS_VALUE);

    joy_.begin(false); // sendState() method is necessary if (false)
}

/**
 * @brief Sends data via USB.
 * 
 * Reads the button states from the Buttons object and updates the joystick interface.
 */
void ComUsb::sendData() {

    #ifdef LUSMDL_DEBUGMODE
    Serial.print("Read Joystick Switch:\t\t\t\t" + String(joyst_->getButtonStatus().pushed)+ "\n");
    Serial.print("The USB send Axis Value for Rotation X is:\t" + String(calculateAxis(joyst_->rotationX_.getData())) + "\n");
    Serial.print("The USB send Axis Value for Rotation Y is:\t" + String(calculateAxis(joyst_->rotationY_.getData())) + "\n");
    //_delay_ms(100);
    #endif

    // joystick

    joy_.setRxAxis(calculateAxis(joyst_->rotationX_.getData()));
    joy_.setRyAxis(calculateAxis(joyst_->rotationY_.getData()));
    joy_.setButton(0, (joyst_->getButtonStatus().pushed || btns_->getData(0).pushed));

    // wheel buttons

    for (uint8_t i = 1; i < BTN_NUMBER; i++) {

        joy_.setButton(i, btns_->getData(i).pushed);

    }

    // steering
    
    joy_.setXAxis(calculateAxis(encoder_->getData()));


    joy_.sendState();
}

/**
 * @brief Calculates the ADC axis value.
 * 
 * Maps the input data range to the USB axis range.
 * 
 * @param data The pod_axis data structure.
 * @return int The calculated ADC axis value.
 */
int16_t ComUsb::calculateAxis(pod_axis data) {

    // make sure every act value is in range

    if (data.act > data.max) {

        data.act = data.max;
    }
    else if (data.act < data.min) {

        data.act = data.min;
    }


    // Map the input range [0, 100] to the output range [-32768, 32767]

    double dataDelta = data.max - data.min;
    double axisDelta = static_cast<double>(MAX_AXIS_VALUE) - static_cast<double>(MIN_AXIS_VALUE);

    // Calculate the scale factor
    double scale = axisDelta / dataDelta;

    // Calculate the output value
    double dataActCal = (data.act - data.min);
    double axisActWithoutOffset = dataActCal * scale;
    double axisActWithOffset = axisActWithoutOffset + static_cast<double>(MIN_AXIS_VALUE);
    int16_t axisAct = static_cast<int16_t>(axisActWithOffset);

    return axisAct;
}

