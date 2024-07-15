#ifndef JOYST_HPP
#define JOYST_HPP

#include "ADCAxis.hpp"
#include "Button.h"
#include "ProjectConfig.hpp"


class Joyst {

    public:

        Joyst();
        ~Joyst();

        ADCAxis rotationX_;
        ADCAxis rotationY_;
        void beginButton();
        pod_button getButtonStatus();





    private:

        pod_button buttonSW_;

        uint8_t readButton();





};
#endif