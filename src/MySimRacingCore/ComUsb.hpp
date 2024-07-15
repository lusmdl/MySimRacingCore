/**
 * @file ComUsb.hpp
 * @brief Definition of the ComUsb class.
 */

#ifndef COM_USB_HPP
#define COM_USB_HPP

#include "ProjectConfig.hpp"
#include <Joystick.h>
#include "Buttons.hpp"
#include "Joyst.hpp"
#include <math.h>

#ifdef LSMDL_DEBUGMODE
#include <WString.h>
#include <Arduino.h>
#endif

class ComUsb {
    
    public:

        ComUsb(Buttons &btns, Joyst &joyst);
        ~ComUsb();
        void begin();
        void sendData();

    private:

        Buttons *btns_;
        Joyst *joyst_;
        
        Joystick_ joy_;


        static const int16_t MIN_AXIS_VALUE = -32768;
        static const int16_t MAX_AXIS_VALUE = 32767;

        int16_t calculateAxis(pod_axis data);
};

#endif // COM_USB_HPP