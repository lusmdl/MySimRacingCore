#ifndef SETUP_DISPLAY_HPP
#define SETUP_DISPLAY_HPP

#include <LiquidCrystal_I2C.h>
#include <avr/delay.h>
#include "ProjectConfig.hpp"

class SetupDisplay {

    public:

        SetupDisplay();
        ~SetupDisplay();
        void begin();
        void show();
        void setNewPage( uint8_t page);

    private:
        LiquidCrystal_I2C *lcd_;

        uint8_t page_;

        void pageBoot();

};







#endif