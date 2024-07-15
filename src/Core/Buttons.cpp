/**
 * @file Buttons.cpp
 * @brief Implementation of the Buttons class.
 */

#include "Buttons.hpp"

/**
 * @brief Constructor for Buttons class.
 * 
 * Initializes the row and column pins, key array, and keypad object.
 */
Buttons::Buttons(TwoWire &wire) :
    wire_(&wire)
{}

/**
 * @brief Destructor for Buttons class.
 * 
 * No dynamic memory allocation is required.
 */
Buttons::~Buttons() {
    delete wire_;
}

/**
 * @brief Initializes the keypad or hardware components.
 */
void Buttons::begin() {
    wire_->begin();
    
}

/**
 * @brief Listens and processes key presses.
 * 
 * Polls the keypad and processes key press events. Updates the data_ array with key press counts.
 */
void Buttons::listener() {

    const uint8_t TWI_MSG_BYTES {2};

    wire_->requestFrom(TWI_ADDR_MY_WHEEL_BTN, TWI_MSG_BYTES);    // request 2 bytes from peripheral device 
    
    if (wire_->available() == TWI_MSG_BYTES) {

        // Check if the peripheral sent the expected number of bytes
        
        uint8_t byte1 = wire_->read(); // Receive the first byte
        uint8_t byte2 = wire_->read(); // Receive the second byte

        // Map the received bytes to the button data structure

        for (int i = 0; i < 8; ++i) {
            data_[i].pushed = (byte1 & (1 << i)) ? 1 : 0; // Map each bit to a button state
        }
        for (int i = 0; i < 8; ++i) {
            data_[8 + i].pushed = (byte2 & (1 << i)) ? 1 : 0; // Map each bit to a button state
        }
    }
    
}

/**
 * @brief Gets the data of a specific button.
 * 
 * @param button The button index.
 * @return pod_button The data of the specified button.
 */
pod_button Buttons::getData(uint8_t button) {

    return data_[button];
}


