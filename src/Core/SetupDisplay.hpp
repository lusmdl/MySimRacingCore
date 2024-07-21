
#ifndef SETUP_DISPLAY_HPP
#define SETUP_DISPLAY_HPP

#include "ProjectConfig.hpp"
#ifndef LUSMDL_DEBUGMODE
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include "EepromAddresses.h"
#include <avr/delay.h>
#include "Joyst.hpp"
#include "TextBoxes.h"
#include "Encoder.hpp"

class SetupDisplay {

    public:

        SetupDisplay(Joyst &joyst, Encoder &encoder, EEPROMClass &eeprom);
        ~SetupDisplay();
        void begin();
        bool runSetup();

    private:
        LiquidCrystal_I2C *lcd_;
        Joyst *joyst_;
        Encoder *encoder_;
        EEPROMClass *eeprom_;

        uint8_t page_;

        bool askForSetup();
        void clearLine(uint8_t line);
        void printLine(uint8_t line, String txt);
        void waitForButtonRelease();

        // pages

        void setupRxMax();
        void setupRxMin();
        void setupRyMax();
        void setupRyMin();
        void setupSteeringZero();
        void setupSteeringTurn();

};






#endif
#endif