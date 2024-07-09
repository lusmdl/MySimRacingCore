#ifndef COM_USB_HPP
#define COM_USB_HPP

#include "ProjectConfig.hpp"
#include <Joystick.h>
#include "Buttons.hpp"

class ComUsb {

    private:

        Joystick_ joy_;
        Buttons *btns_;


    public:

        ComUsb(Buttons &btns);
        ~ComUsb();
        void begin();
        void sendData();
};

#endif // COM_USB_HPP