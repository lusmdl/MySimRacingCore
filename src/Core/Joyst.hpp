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
        void setRxCenter(float center);
        void setRyCenter(float center);
        void setRxCenter(int center);
        void setRyCenter(int center);
        int getRxCenter();
        int getRyCenter();
        pod_axis getDataRx();
        pod_axis getDataRy();
        pod_button getButtonStatus();





    private:

        pod_button buttonSW_;
        float centerRx_;
        float centerRy_;
        const float TOLERANCE_;

        uint8_t readButton();
        float checkTolerance(float act, float target, float tolerance, float smooth_value);





};
#endif