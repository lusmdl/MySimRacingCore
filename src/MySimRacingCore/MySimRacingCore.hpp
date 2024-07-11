#ifndef MY_SIM_RACING_CORE_HPP
#define MY_SIM_RACING_CORE_HPP

#include "ComUsb.hpp"
#include "Buttons.hpp"
#include "Encoder.hpp"


class MySimRacingCore {

    


    public:
        MySimRacingCore();
        void setup();
        void loop();
        void encoderHandleInterrupt();

    private:

        Buttons buttons_;
        Encoder encoder_;
        ComUsb com_;

};

#endif // MY_SIM_RACING_CORE_HPP

