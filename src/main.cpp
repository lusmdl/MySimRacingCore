#include <Arduino.h>
#include "MySimRacingCore/MySimRacingCore.hpp"

MySimRacingCore core;

void setup(void) {

    core.setup();
}

void loop(void) {

    core.loop();
}

// ISR for INT0
ISR(INT0_vect) {
    core.encoderHandleInterrupt();
}

// ISR for INT1
ISR(INT1_vect) {
    core.encoderHandleInterrupt();
}