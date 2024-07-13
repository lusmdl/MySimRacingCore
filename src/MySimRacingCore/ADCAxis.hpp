/**
 * @file ADCAxis.hpp
 * 
 * @brief Definition of the ADCAxis class.
 * 
 * 
 */


#ifndef ADC_AXIS_HPP
#define ADC_AXIS_HPP


#include <avr/io.h>
#include <stdint.h>
#include "Axis.h"

#ifndef __AVR_ATmega32U4__
#error "This code is designed to work with ATmega32U4 microcontrollers only. Please use a compatible microcontroller or modify the encoder code to match your hardware."
#endif

/**
 * @brief Class for managing an analog axis with ADC
 */
class ADCAxis {

    public:
        
        ADCAxis(uint8_t pin);
        void begin();
        void updateRawData();
        void setMinHere(double min);
        void setMaxHere(double max);
        pod_axis getData();


    private:
        pod_axis data_;
        uint8_t pin_;
        int rawMax_;
        int rawAct_;
        int rawMin_;
        int readADC();

};

#endif // ADC_AXIS_HPP
