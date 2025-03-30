
#ifndef SETUP_DISPLAY_HPP
#define SETUP_DISPLAY_HPP

#include "ProjectConfig.hpp"
#ifndef LUSMDL_DEBUGMODE
//#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <avr/delay.h>
#include "Joyst.hpp"
#include "TextBoxes.h"
#include "Encoder.hpp"
#include "Pedals.hpp"
#include "EepromAdresses.h"

class SetupDisplay {

    public:

        SetupDisplay(Joyst &joyst, Pedals &pedal, Encoder &encoder, EEPROMClass &eeprom, TwoWire &wire);
        ~SetupDisplay();
        void begin();
        void runSetup();

    private:
        Joyst *joyst_;
        Pedals *pedal_;
        Encoder *encoder_;
        EEPROMClass *eeprom_;
        TwoWire *wire_;

        uint8_t page_;
        int value_;
        uint8_t wait_;
        void waitForButtonRelease();

};






#endif
#endif