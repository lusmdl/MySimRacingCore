/**
 * @file Buttons.hpp
 * @brief Definition of the Buttons class.
 */

#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include "Button.h"
#include <Wire.h>
#include "ProjectConfig.hpp"

class Buttons {

    public:
        Buttons(TwoWire &wire);
        ~Buttons();
        void listener();
        pod_button getData(uint8_t button);

    private:
        pod_button data_[BTN_NUMBER];
        TwoWire *wire_;

};

#endif // BUTTONS_HPP