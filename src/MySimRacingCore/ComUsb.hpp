#ifndef COM_USB_HPP
#define COM_USB_HPP

#include "ProjectConfig.hpp"
#include <Joystick.h>

class ComUsb
{
private:
    Joystick_ *joy_;

public:
    ComUsb();
    ~ComUsb();
    
    void begin();
    void sendData();
};



#endif // COM_USB_HPP
