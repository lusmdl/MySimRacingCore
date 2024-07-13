/**
 * @file ComUsb.hpp
 * @brief Definition of the ComUsb class.
 */

#ifndef COM_USB_HPP
#define COM_USB_HPP

#include "ProjectConfig.hpp"
#include <Joystick.h>
#include "Buttons.hpp"

class ComUsb {
    
    public:

        ComUsb(Buttons &btns);
        ~ComUsb();
        void begin();
        void sendData();

    private:

        Buttons *btns_;
        Joystick_ joy_;
};

#endif // COM_USB_HPP