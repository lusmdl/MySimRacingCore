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
ComUsb::ComUsb(Buttons &btns, Joyst &joyst, Pedals &pedal, Encoder &encoder) :
    btns_(&btns),
    joyst_(&joyst),
    pedal_(&pedal),
    encoder_(&encoder),
    joy_(
        JOYSTICK_DEFAULT_REPORT_ID, // REPORT_ID        Hid report id
        JOYSTICK_TYPE_MULTI_AXIS,   // JOYSTICK_TYPE    Type of device: JOYSTICK, GAMEPAD, MULTI_AXIS
        BTN_NUMBER,                 // button count     [0-32]
        0,                          // Hat Switch count [0,1,2]
        #ifdef FFB
        true,                       // X Axis enable    True or False
        #endif
        #ifndef FFB
        false,                      // X Axis enable    True or False
        #endif
        false,                      // Y Axis enable    True or False
        false,//true,                       // Z Axis enable    True or False
        true,                       // Rx Axis enable   True or False
        true,                       // Ry Axis enable   True or False
        false,                      // Rz Axis enable   True or False
        false,                      // Rudder enable    True or False
        false,                      // Throttle enable  True or False
        true,                       // Accelerator enable True or False
        true,                       // Brake enable     True or False
        #ifdef FFB
        false                       // Steering enable  True or False
        #endif
        #ifndef FFB
        true                        // Steering enable  True or False
        #endif
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
    
    //joy_.setYAxisRange(AXIS_MIN_USB, AXIS_MAX_USB);
    joy_.setZAxisRange(AXIS_MIN_USB, AXIS_MAX_USB);
    joy_.setRxAxisRange(AXIS_MIN_USB, AXIS_MAX_USB);
    joy_.setRyAxisRange(AXIS_MIN_USB, AXIS_MAX_USB);
    //joy_.setRzAxisRange(AXIS_MIN_USB, AXIS_MAX_USB);
    //joy_.setRudderRange(AXIS_MIN_USB, AXIS_MAX_USB);
    //joy_.setThrottleRange(AXIS_MIN_USB, AXIS_MAX_USB);
    joy_.setAcceleratorRange(AXIS_MIN_USB, AXIS_MAX_USB);
    joy_.setBrakeRange(AXIS_MIN_USB, AXIS_MAX_USB);
    #ifdef FFB
    joy_.setXAxisRange(AXIS_MIN_USB, AXIS_MAX_USB);
    #endif
    #ifndef FFB
    joy_.setSteeringRange(AXIS_MIN_USB, AXIS_MAX_USB);
    #endif
    
    //set Timer3
    // The ISR of timer 3 have to be set in the main.cpp!!!

    cli();
    TCCR3A = 0; //set TCCR1A 0
    TCCR3B = 0; //set TCCR1B 0
    TCNT3  = 0; //counter init
    OCR3A = 399;
    TCCR3B |= (1 << WGM32); //open CTC mode
    TCCR3B |= (1 << CS31); //set CS11 1(8-fold Prescaler)
    TIMSK3 |= (1 << OCIE3A);
    sei();

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

    joy_.setRxAxis(calculateAxis(joyst_->getDataRx()));
    joy_.setRyAxis(calculateAxis(joyst_->getDataRy()));
    joy_.setButton(0, (joyst_->getButtonStatus().pushed || btns_->getData(0).pushed));

    // pedals

    joy_.setAccelerator(calculateAxis(pedal_->throttle_.getData(0.1 , 0.5)));
    joy_.setBrake(calculateAxis(pedal_->brake_.getData(0.5 , 0.01)));

    // wheel buttons (*Button 0 is handeld at section: joystick)

    for (uint8_t i = 1; i < BTN_NUMBER; i++) {

        joy_.setButton(i, btns_->getData(i).pushed);

    }

    // steering
    
    #ifdef FBB
    joy_.setXAxis(calculateAxis(encoder_->getData()));
    #endif
    #ifndef FFB
    joy_.setSteering(calculateAxis(encoder_->getData()));
    #endif

    joy_.sendState();
}

void ComUsb::receiveData() {

    // have to be called in the ISR of timer 3 in main.cpp

    joy_.getUSBPID();
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

    float dataDelta = data.max - data.min;
    float axisDelta = static_cast<float>(AXIS_MAX_USB) - static_cast<float>(AXIS_MIN_USB);

    // Calculate the scale factor
    float scale = axisDelta / dataDelta;

    // Calculate the output value
    float dataActCal = (data.act - data.min);
    float axisActWithoutOffset = dataActCal * scale;
    float axisActWithOffset = axisActWithoutOffset + static_cast<float>(AXIS_MIN_USB);
    int16_t axisAct = static_cast<int16_t>(axisActWithOffset);

    return axisAct;
}

