#ifndef PEDALS_HPP
#define PEDALS_HPP

#include "ADCAxis.hpp"
#include "ProjectConfig.hpp"

class Pedals {

    public:
        Pedals();
        ~Pedals();

        ADCAxis throttle_;
        ADCAxis brake_;
};




#endif