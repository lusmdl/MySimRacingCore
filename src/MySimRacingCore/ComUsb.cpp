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
ComUsb::ComUsb(Buttons &btns, Joyst &joyst) :
    btns_(&btns),
    joyst_(&joyst),
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

    for (uint8_t i = 0; i < BTN_NUMBER; i++) {

        joy_.setButton(i, btns_->getData(i).pushed);
    }

    #ifdef LSMDL_DEBUGMODE
    Serial.print("The USB send Axis Value for Rotation X is: " + String(calculateAxis(joyst_->rotationX_.getData())) + "\n");
    Serial.print("The USB send Axis Value for Rotation Y is: " + String(calculateAxis(joyst_->rotationY_.getData())) + "\n");
    //_delay_ms(100);
    #endif

    joy_.setRxAxis(calculateAxis(joyst_->rotationX_.getData()));
    joy_.setRyAxis(calculateAxis(joyst_->rotationY_.getData()));
    #ifdef LSMDL_DEBUGMODE
    Serial.print("Read Joystick Switch: " + String(joyst_->getButtonStatus().pushed)+ "\n");
    #endif
    joy_.setButton(17, joyst_->getButtonStatus().pushed);

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

    #ifdef LSMDL_DEBUGMODE
    Serial.print("calculateAxis!!!\n");
    #endif

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

    #ifdef LSMDL_DEBUGMODE
    Serial.print("The calculated values:");
    //Serial.println("\tdata_delta " + String(dataDelta));
    //Serial.println("\taxis_delta "+ String(axisDelta));
    //Serial.println("\tscale "+ String(scale));
    //Serial.println("\tdataActCal " + String(dataActCal));
    //Serial.println("\axisActWithoutOffset " + String(axisActWithoutOffset));
    Serial.println("\axisActWithOffset " + String(axisActWithOffset));
    //Serial.println("\axisAct " + String(axisAct));
    Serial.println("calculation end!!!");
    _delay_ms(100);
    #endif

    return axisAct;
}

