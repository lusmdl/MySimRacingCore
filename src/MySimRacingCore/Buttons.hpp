#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include <MyAvr.hpp>
#include "ProjectConfig.hpp"


struct pod_buttonmatrix {
    bool pushed;
};


class Buttons {


    public:
        Buttons();
        ~Buttons();
        void begin();
        void listner();

        pod_buttonmatrix matrix_[BTN_NUMBER];

    private:

        MyButtonMatrix2x2 *btnA_;
        MyButtonMatrix2x2 *btnB_;
        MyButtonMatrix2x2 *btnC_;
        MyButtonMatrix2x2 *btnD_;
};


#endif // BUTTONS_HPP

