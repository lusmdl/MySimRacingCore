/**
 * @file Encoder.hpp
 * @brief Definition of the Encoder class.
 */

#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Axis.h"
#include "ProjectConfig.hpp"

// Ensure the code is only compiled for ATmega32U4
#ifndef __AVR_ATmega32U4__
#error "This code is designed to work with ATmega32U4 microcontrollers only. Please use a compatible microcontroller or modify the encoder code to match your hardware."
#endif


class Encoder {

    public:

        Encoder(uint8_t pinA, uint8_t pinB);
        void begin();
        int getPosition() const;
        void setZero();
        float setFactor();
        void setFactor(float new_factor);
        pod_axis getData();

        uint8_t pinA_;
        uint8_t pinB_;
        volatile int32_t position_;
        volatile int8_t oldState_;

        static const int8_t KNOBDIR[];
        static const float STEERING_MAX_DEG;
        static const float STEERING_FULL_TURN;


    private:
        pod_axis data_;
        int fullturn_;
        float factor_;
};



#endif // ENCODER_HPP
