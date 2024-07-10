#ifndef MY_SIM_RACING_CORE_HPP
#define MY_SIM_RACING_CORE_HPP

#include "ComUsb.hpp"
#include "Buttons.hpp"
//#include "Pedals.hpp"
//#include "Shifting.hpp"
//#include "WheeleBase.hpp"



class MySimRacingCore {


    public:
        MySimRacingCore();
        void setup();
        void loop();

    private:

        Buttons buttons_;
        ComUsb com_;
        //Pedals pedals_;
        //Shifting shift_;
        //WheelBase wheele_;

};

#endif // MY_SIM_RACING_CORE_HPP

