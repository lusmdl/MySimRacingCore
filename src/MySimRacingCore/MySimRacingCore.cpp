#include "MySimRacingCore.hpp"

MySimRacingCore::MySimRacingCore() :    
    com_(buttons_)
    {}

void MySimRacingCore::setup() {

    
    #ifdef LSMDL_DEBUGMODE
    Serial.begin(9600);
    #endif

    buttons_.begin();
    
    com_.begin();

}

void MySimRacingCore::loop() {

    _delay_ms(1);

    buttons_.listener();
    
    com_.sendData();
}