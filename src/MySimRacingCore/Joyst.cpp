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
    rotationY_(SHIFTER_Y_PIN)  // Assuming SHIFTER_Y_PIN is defined in ProjectConfig.hpp
{}

/**
 * @brief Destructor for Joyst class.
 */
Joyst::~Joyst() {

}


/**
 * @brief Initializes the joystick.
 * 
 * Sets up the ADC axes and configures the button pin.
 */
void Joyst::beginButton() {

    #ifdef __AVR_ATmega32U4__
    // Configure the button pin (D11 -> PB7) as input with pull-up resistor
    DDRB &= ~(1 << DDB7); // Set PB7 as input
    PORTB |= (1 << PORTB7); // Enable pull-up resistor on PB7
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
    if (PINB & (1 << PINB7)) {
        // Button not pressed
        return 0;
    } else {
        // Button pressed
        return 1;
    }
    #endif
}