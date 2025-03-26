
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
#include "Pedals.hpp"

class SetupDisplay {

    public:

        SetupDisplay(Joyst &joyst, Pedals &pedal, Encoder &encoder, EEPROMClass &eeprom);
        ~SetupDisplay();
        void begin();
        uint8_t runSetup();
        void showSteering();
        void dark();

    private:
        LiquidCrystal_I2C *lcd_;
        Joyst *joyst_;
        Pedals *pedal_;
        Encoder *encoder_;
        EEPROMClass *eeprom_;

        uint8_t page_;

        static constexpr float MAX_AXIS                 = 100.00;
        static constexpr float MIN_AXIS                 = 00.00; 

        static constexpr int STORE_ADDR_RX_MAX          = 0;
        static constexpr int STORE_ADDR_RX_MIN          = 16;
        static constexpr int STORE_ADDR_RY_MAX          = 32;
        static constexpr int STORE_ADDR_RY_MIN          = 48;
        static constexpr int STORE_ADDR_FACTOR          = 64;
        static constexpr int STORE_ADDR_THROTTLE_MAX    = 96;
        static constexpr int STORE_ADDR_THROTTLE_MIN    = 112;
        static constexpr int STORE_ADDR_BRAKE_MAX       = 128;
        static constexpr int STORE_ADDR_BRAKE_MIN       = 144;
        static constexpr int STORE_ADDR_RX_CENTER       = 160;
        static constexpr int STORE_ADDR_RY_CENTER       = 176;

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
        void setupThrottleMax();
        void setupThrottleMin();
        void setupBrakeMax();
        void setupBrakeMin();

};






#endif
#endif