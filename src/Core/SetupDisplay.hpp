
#ifndef SETUP_DISPLAY_HPP
#define SETUP_DISPLAY_HPP

#include "ProjectConfig.hpp"
#ifndef LUSMDL_DEBUGMODE
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
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
        void showSteering();

    private:
        LiquidCrystal_I2C *lcd_;
        Joyst *joyst_;
        Encoder *encoder_;
        EEPROMClass *eeprom_;

        uint8_t page_;

        static const float MAX_AXIS             = 100.00;
        static const float MIN_AXIS             = 00.00; 

        static const int STORE_ADDR_RX_MAX      = 0;
        static const int STORE_ADDR_RX_MIN      = 16;
        static const int STORE_ADDR_RY_MAX      = 32;
        static const int STORE_ADDR_RY_MIN      = 48;
        static const int STORE_ADDR_FACTOR      = 80;

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