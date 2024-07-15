/**
 * @file Buttons.hpp
 * @brief Definition of the Buttons class.
 */

#ifndef BUTTONS_HPP
#define BUTTONS_HPP




#include "Button.h"
#include <Wire.h>
//#include <Keypad.h>
#include "ProjectConfig.hpp"


class Buttons {

    public:
        Buttons(TwoWire &wire);
        ~Buttons();
        void begin();
        void listener();
        pod_button getData(uint8_t button);

    private:
        pod_button data_[BTN_NUMBER];
        TwoWire *wire_;



        //uint8_t rowpins_[BTN_MATRIX_R];
        //uint8_t columnspins_[BTN_MATRIX_L];
        //char keyarray_[BTN_MATRIX_R][BTN_MATRIX_L];
        //Keypad keys_;

        //int getmap(char key);
        //char getmap(int key);
        //char lasteventkey_; // store the key - otherwise i have problems
};



#endif // BUTTONS_HPP