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
#ifndef LSMDL_DEBUGMODE
#include "SetupDisplay.hpp"
#endif

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

        #ifndef LSMDL_DEBUGMODE
        SetupDisplay display_;
        #endif
    
        ComUsb com_;
};

#endif // MY_SIM_RACING_CORE_HPP

