#ifndef PEDALS_HPP
#define PEDALS_HPP


/*
#include "MySimRacingCore.hpp"
#include "Throttle.hpp"
#include "Brake.hpp"
#include "Clutch.hpp"

struct pod_pedals {

    uint8_t max;
    uint8_t actual;
    double actualPercent;
    uint8_t min;
    uint8_t active;
};


class Pedals {

    public:
        Pedals(MyAtmega32u4 &controller);
        ~Pedals();

        void begin();
        void readPositions();
        void sendPositionsToPc();

    private:

        Throttle accel_;
        Brake brake_;
        Clutch clutch_;
    
        MyAtmega32u4 *controller_;
};


class interface_Pedals {


    public:
        virtual ~interface_Pedals() = default;
        virtual void begin() = 0;
        virtual uint8_t read() = 0;
        virtual double getValue() const = 0;
        virtual void uploadSettings() = 0;
        virtual void downloadSettings() = 0;
};


*/
#endif // PEDALS_HPP
