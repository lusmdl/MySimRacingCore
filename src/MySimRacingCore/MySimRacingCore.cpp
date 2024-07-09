#include "MySimRacingCore.hpp"

MySimRacingCore::MySimRacingCore() :    
    com_(buttons_)
    {}

void MySimRacingCore::setup() {

    
    com_.begin();
}

void MySimRacingCore::loop() {

    com_.sendData();
}