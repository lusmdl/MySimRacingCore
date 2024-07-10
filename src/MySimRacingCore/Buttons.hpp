#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include <Keypad.h>
#include "ProjectConfig.hpp"

struct pod_buttonmatrix {

    uint8_t pushed;
};

class Buttons {

    public:

        Buttons();
        ~Buttons();
        void begin();
        void listener();
        pod_buttonmatrix data_[BTN_NUMBER];


    private:
    
        uint8_t rowpins_[BTN_MATRIX_R];
        uint8_t columnspins_[BTN_MATRIX_L];
        char keyarray_[BTN_MATRIX_R][BTN_MATRIX_L];
        Keypad keys_;
};


#endif // BUTTONS_HPP