
#ifndef SETUP_DISPLAY_HPP
#define SETUP_DISPLAY_HPP

#include "ProjectConfig.hpp"
//#ifndef LUSMDL_DEBUGMODE
#include <LiquidCrystal_I2C.h>
#include <avr/delay.h>
#include "Joyst.hpp"

class SetupDisplay {

    public:

        SetupDisplay(Joyst &joyst);
        ~SetupDisplay();
        void begin();
        bool runSetup();

    private:
        LiquidCrystal_I2C *lcd_;
        Joyst *joyst_;

        uint8_t page_;

        void setNewPage( uint8_t page);

        bool askForSetup();

};






//#endif
#endif