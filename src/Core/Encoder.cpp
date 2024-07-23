/**
 * @file Encoder.hpp
 * @brief Implementations of the Encoder class.
 */

#include "Encoder.hpp"



const int8_t Encoder::KNOBDIR[] = {
  0, 1, -1, 0,
  -1, 0, 0, 1,
  1, 0, 0, -1,
  0, -1, 1, 0
};

const float Encoder::STEERING_MAX_DEG     = 540.00;
const float Encoder::STEERING_FULL_TURN   = 360.00;


Encoder::Encoder(uint8_t pinA, uint8_t pinB) : 
    pinA_(pinA),
    pinB_(pinB),
    position_(0), 
    oldState_(0),
    fullturn_(0),
    factor_(1.00)
{
    data_.max = STEERING_MAX_DEG;
    data_.min = STEERING_MAX_DEG * (-1);
}

void Encoder::begin() {
}

int Encoder::getPosition() const {
    return position_;
}

void Encoder::setZero() {
    
    position_ = 0;
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


