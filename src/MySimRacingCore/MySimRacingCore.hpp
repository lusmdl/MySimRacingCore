/**
 * @file MySimRacingCore.hpp
 * @brief Definition of the MySimRacingCore class.
 */

#ifndef MY_SIM_RACING_CORE_HPP
#define MY_SIM_RACING_CORE_HPP

#include "ComUsb.hpp"
#include "Buttons.hpp"
#include "Encoder.hpp"
#include "Joyst.hpp"

class MySimRacingCore {

    public:

        MySimRacingCore();
        void setup();
        void loop();
        void encoderHandleInterrupt();

    private:

        Buttons buttons_;
        Encoder encoder_;
        Joyst joy_;

        ComUsb com_;
};

#endif // MY_SIM_RACING_CORE_HPP

