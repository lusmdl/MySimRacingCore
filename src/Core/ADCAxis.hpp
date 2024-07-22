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
#include "ProjectConfig.hpp"

#ifdef LUSMDL_DEBUGMODE
#include <WString.h>
#include <Arduino.h>
#endif

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
        int readADC();
        int setMin(float min);
        void setMin(float min, int raw);
        int setMax(float max);
        void setMax(float max, int raw);
        pod_axis getData();


    private:
    
        uint8_t pin_;
        int rawMin_;
        int rawMax_;
        int rawAct_;

        pod_axis data_;

};

#endif // ADC_AXIS_HPP
