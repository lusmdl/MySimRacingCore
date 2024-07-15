/**
 * @file Encoder.hpp
 * @brief Definition of the Encoder class.
 */

#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Axis.h"

// Ensure the code is only compiled for ATmega32U4
#ifndef __AVR_ATmega32U4__
#error "This code is designed to work with ATmega32U4 microcontrollers only. Please use a compatible microcontroller or modify the encoder code to match your hardware."
#endif


class Encoder {
public:
    Encoder();
    void begin();
    int getPosition() const;
    void handleInterrupt();
    pod_axis getData();

private:
    pod_axis data_;
    volatile int position_;
    volatile uint8_t lastState_;

};

#endif // ENCODER_HPP
