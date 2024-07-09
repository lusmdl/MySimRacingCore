
#include "MySimRacingCore.hpp"

MySimRacingCore::MySimRacingCore() {

}

void MySimRacingCore::setup() {

    com_.begin();

    


}

void MySimRacingCore::loop() {

    com_.sendData();



}
