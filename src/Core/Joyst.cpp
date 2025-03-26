/**
 * @file Joyst.cpp
 * @brief Implementation of the Joyst class.
 */ 

#include "Joyst.hpp"

/**
 * @brief Constructor for Joyst class.
 * 
 * Initializes the rotationX_ and rotationY_ ADCAxis objects.
 */
Joyst::Joyst() :
    rotationX_(SHIFTER_X_PIN), // Assuming SHIFTER_X_PIN is defined in ProjectConfig.hpp
    rotationY_(SHIFTER_Y_PIN),  // Assuming SHIFTER_Y_PIN is defined in ProjectConfig.hpp
    centerRx_(00.00),
    centerRy_(00.00),
    TOLERANCE_(2.00)

{}

/**
 * @brief Destructor for Joyst class.
 */
Joyst::~Joyst() {}


/**
 * @brief Initializes the joystick.
 * 
 * Sets up the ADC axes and configures the button pin.
 */
void Joyst::beginButton() {

    #ifdef __AVR_ATmega32U4__
    // Configure the button pin (D11 -> PB7) as input with pull-up resistor
    DDRB &= ~(1 << JOYSTICK_BTN_PIN); // Set PB7 as input
    PORTB |= (1 << JOYSTICK_BTN_PIN); // Enable pull-up resistor on PB7
    #endif
}

/**
 * @brief Gets the status of the button.
 * 
 * Calls the readButton method to update the button status.
 * 
 * @return pod_button The status of the button.
 */
pod_button Joyst::getButtonStatus() {

    buttonSW_.pushed = readButton();
    return buttonSW_;
}

/**
 * @brief Reads the status of the button.
 * 
 * @return uint8_t The status of the button (1 if pressed, 0 if not pressed).
 */
uint8_t Joyst::readButton() {
    
    #ifdef __AVR_ATmega32U4__
    // Read the button pin (D11 -> PB7)
    if (PINB & (1 << JOYSTICK_BTN_PIN)) {
        // Button not pressed
        return 0;
    } else {
        // Button pressed
        return 1;
    }
    #endif
}

void Joyst::setRxCenter(float center) {

    centerRx_ = center;
}

void Joyst::setRyCenter(float center) {

    centerRy_ = center;
}

void Joyst::setRxCenter(int center) {
 
    centerRx_ = static_cast<float>(center);
}

void Joyst::setRyCenter(int center) {

    centerRy_ = static_cast<float>(center);
}

int Joyst::getRxCenter() {

    return static_cast<int>(centerRx_);
}

int Joyst::getRyCenter() {

    return static_cast<int>(centerRy_);
}

/**
 * @brief Adjusts the actual joystick value to the center if within a tolerance range.
 * 
 * This function retrieves the ADC axis data and checks if the actual value (`act`) 
 * falls within a defined tolerance around 50%. If so, the value is adjusted to 50.0 
 * to ensure a centered position. If the value is outside this range, it remains unchanged. 
 * The minimum (`min`) and maximum (`max`) values are not modified.
 * 
 * @return pod_axis A structure containing the corrected or original ADC axis data.
 */
pod_axis Joyst::getDataRx() {

    // Copy original data

    pod_axis d = rotationX_.getData();    

    d.act = checkTolerance(d.act, centerRx_, TOLERANCE_, (d.max-d.max)*0.5);


    return d; // Return modified or original value
}

/**
 * @brief Adjusts the actual joystick value to the center if within a tolerance range.
 * 
 * This function retrieves the ADC axis data and checks if the actual value (`act`) 
 * falls within a defined tolerance around 50%. If so, the value is adjusted to 50.0 
 * to ensure a centered position. If the value is outside this range, it remains unchanged. 
 * The minimum (`min`) and maximum (`max`) values are not modified.
 * 
 * @return pod_axis A structure containing the corrected or original ADC axis data.
 */
pod_axis Joyst::getDataRy() {

    // Copy original data

    pod_axis d = rotationY_.getData();    

    d.act = checkTolerance(d.act, centerRy_, TOLERANCE_, (d.max-d.max)*0.5);

    return d; // Return modified or original value
}

/**
 * 
 * @brief Check a target value with area around (tolerance) and give back a smothed value or the actual value
 * 
 * 
 * 
 * 
 */
float Joyst::checkTolerance(float act, float target, float tolerance,  float smooth_value) {

    // Adjust act value if within tolerance range

    if (act > (target - tolerance) && act < (target + tolerance)) {

        // Smooth value to center

        return smooth_value;
    }

    return act;
}