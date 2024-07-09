#ifndef MY_SIM_RACING_CORE_HPP
#define MY_SIM_RACING_CORE_HPP

#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <MyAvr.hpp>
#include <MyNeoPixels.hpp>



#include "ComUsb.hpp"
//#include "Buttons.hpp"
//#include "Pedals.hpp"
//#include "Shifting.hpp"
//#include "WheeleBase.hpp"



class MySimRacingCore {


    public:
        MySimRacingCore();
        void setup();
        void loop();

    private:

        MyAtmega32u4 controller_;
        //Com usb_;
        ComUsb com_;
        //Buttons buttons_;
        //Pedals pedals_;
        //Shifting shift_;
        //WheelBase wheele_;

};

#endif // MY_SIM_RACING_CORE_HPP

