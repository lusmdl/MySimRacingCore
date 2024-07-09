#ifndef COM_USB_HPP
#define COM_USB_HPP

//#include <MySimRacingCore.hpp> //problems, i don´t know

#include <Joystick.h>

class ComUsb
{
private:
    Joystick_ *joy_;

public:
    ComUsb();
    ~ComUsb();
    
    void begin();
    void send();
};



#endif // COM_USB_HPP
