/**
 * @file Encoder.hpp
 * @brief Implementations of the Encoder class.
 */

#include "Encoder.hpp"


Encoder::Encoder() : 
    position_(0), 
    lastState_(0)
{
    data_.max = STEERING_MAX_DEG;
    data_.min = STEERING_MAX_DEG * (-1);
}

void Encoder::begin() {

    cli(); // Disable global interrupts

    #ifdef __AVR_ATmega32U4__

    // Configure INT0 and INT1 for any logical change
    EICRA |= (1 << ISC00) | (1 << ISC10);
    EIMSK |= (1 << INT0) | (1 << INT1);

    // Initialize lastState_ with the initial state of the encoder pins
    lastState_ = (ENCODER_REG_PIN & ((1 << ENCODER_A_PIN) | (1 << ENCODER_B_PIN))) >> 2;

    #endif

    sei(); // Enable global interrupts
}

int Encoder::getPosition() const {
    return position_;
}

void Encoder::setZero() {
    
    position_ = 0;
}

/**
 * @brief Handles the interrupt triggered by changes on the encoder's A and B lines.
 *
 * This method processes the interrupts caused by changes on the encoder's A and B lines (connected to INT0 and INT1).
 * It uses the state transitions of the encoder to count the rotation. Each transition calls this method, which calculates
 * the transition and updates the position counter accordingly.
 */
void Encoder::handleInterrupt() {

    // Read the current state of INT0 and INT1
    // 
    // The method handleInterrupt in the class Encoder is used to process interrupts
    // triggered by changes in the inputs of the optical encoder.
    //
    //
    // Summary
    //
    // This method uses the encoder's state transitions to count rotations. 
    // Each transition of the states of pins INT0 and INT1 (the A and B lines of the encoder) 
    // results in an interrupt that calls the handleInterrupt method. 
    // This method calculates the transition and updates the position counter accordingly.

    
    #ifdef __AVR_ATmega32U4__

    // Read current state of INT0 and INT1
    //
    // This reads the current state of the INT0 and INT1 pins (corresponding to pins 2 and 3 on the Arduino Micro).
    // PIND is the register that holds the state of digital pins 0-7.
    // (PIND & ((1 << PIND2) | (1 << PIND3))) isolates the bits for pins 2 and 3.
    // >> 2 shifts the bits right, placing them at the lower bits (0 and 1) of the state variable.
    uint8_t state = (ENCODER_REG_PIN & ((1 << ENCODER_A_PIN) | (1 << ENCODER_B_PIN))) >> 2; 

    // Calculate the transition state
    // 
    // HThe lastState_ is shifted left by two bits and combined with the current state.
    // This results in four bits representing the state transitions.
    uint8_t transition = (lastState_ << 2) | state;
    #endif

    // Evaluate the state transitions
    // 
    // Depending on the four-bit combinations (transitions), the position_ counter is either incremented or decremented.
    // The four cases in each group represent a step in either the clockwise or counterclockwise direction.
    switch (transition) {
        case 0b0001:
        case 0b0111:
        case 0b1000:
        case 0b1110:
            position_++;
            break;
        case 0b0010:
        case 0b0100:
        case 0b1011:
        case 0b1101:
            position_--;
            break;
        default:
            break;
    }

    /* // maybe this is also good? Code Copilot said this

    // Update the position based on the state transition table
    static const int8_t transitionTable[16] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};
    position_ += transitionTable[transition];
    */

    // Store the current state
    // 
    // The current state is saved to be used as the lastState_ in the next interrupt.
    lastState_ = state;
}

pod_axis Encoder::getData() {

    data_.act = position_ * factor_;

    
    return data_;
}

float Encoder::setFactor() {

    // set the full turn marker at the current position (360°)
    fullturn_ = position_;

    // calculate the factor
    factor_ = (STEERING_FULL_TURN / fullturn_);

    return factor_;
}

void Encoder::setFactor(float new_factor) {

    factor_ = new_factor;
}
