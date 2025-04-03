#include "SetupDisplay.hpp"
#ifndef LUSMDL_DEBUGMODE


SetupDisplay::SetupDisplay(Joyst &joyst, Pedals &pedal, Encoder &encoder, EEPROMClass &eeprom, TwoWire &wire):
    joyst_(&joyst),
    pedal_(&pedal),
    encoder_(&encoder),
    eeprom_(&eeprom),
    wire_(&wire),
    page_(0),
    wait_(0)
{}


SetupDisplay::~SetupDisplay() {}


void SetupDisplay::begin() {

    // In this method, we initialized the settings
    // This schould be performed every time, otherwise the microcontroller does not have the correct settings

    // temporary used variables for restoring

    int eepromInt;
    float eepromFloat;

    // restore Joystick

    eeprom_->get(STORE_ADDR_RX_MAX, eepromInt);
    joyst_->rotationX_.setMax(AXIS_MAX_PHYSIC, eepromInt);

    eeprom_->get(STORE_ADDR_RX_MIN, eepromInt);
    joyst_->rotationX_.setMin(AXIS_MIN_PHYSIC, eepromInt);


    eeprom_->get(STORE_ADDR_RX_CENTER, eepromInt);
    joyst_->setRxCenter(eepromInt);


    // restore Ry-Axis

    eeprom_->get(STORE_ADDR_RY_MAX, eepromInt);
    joyst_->rotationY_.setMax(AXIS_MAX_PHYSIC, eepromInt);
    
    eeprom_->get(STORE_ADDR_RY_MIN, eepromInt);
    joyst_->rotationY_.setMin(AXIS_MIN_PHYSIC, eepromInt);


    eeprom_->get(STORE_ADDR_RY_CENTER, eepromInt);
    joyst_->setRyCenter(eepromInt);

    // restore Throttle-Axis

    eeprom_->get(STORE_ADDR_THROTTLE_MAX, eepromInt);
    pedal_->throttle_.setMax(AXIS_MAX_PHYSIC, eepromInt);
    
    eeprom_->get(STORE_ADDR_THROTTLE_MIN, eepromInt);
    pedal_->throttle_.setMin(AXIS_MIN_PHYSIC, eepromInt);


    // restore Brake-Axis

    eeprom_->get(STORE_ADDR_BRAKE_MAX, eepromInt);
    pedal_->brake_.setMax(AXIS_MAX_PHYSIC, eepromInt);
    
    eeprom_->get(STORE_ADDR_BRAKE_MIN, eepromInt);
    pedal_->brake_.setMin(AXIS_MIN_PHYSIC, eepromInt);
    

    // restor Steering

    eeprom_->get(STORE_ADDR_FACTOR, eepromFloat);
    encoder_->setFactor(eepromFloat);
}


void SetupDisplay::runSetup() {


    // without button push

    switch (page_) {
           
        
        case 0 : // Zero Steering

        value_ = encoder_->getPosition();
        break;
        

        case 1 : // ask user, if want´s to make setup wizard

        if (wait_ > LCD_WAIT_UNTIL) {
            
            page_ = 255;
        }
        _delay_ms(LCD_WAIT_TIME);
        value_ = wait_++;
        break;

        case 255: // no setup 
        
        value_ = encoder_->getPosition();
        break;

        case 2 : // Rotary X Axis MAX

        value_ = static_cast<int>(joyst_->rotationX_.getData().act);          
        break;


        case 3 : // Rotary X Axis MIN

        value_ = static_cast<int>(joyst_->rotationX_.getData().act);   
        break;


        case 4 : // Rotary Y Axis MAX

        value_ = static_cast<int>(joyst_->rotationY_.getData().act);   
        break;


        case 5 : // Rotary Y Axis MIN

        value_ = static_cast<int>(joyst_->rotationY_.getData().act);   
        break;


        case 6 : // Steering turn

        value_ = encoder_->getPosition();
        break;


        case 7 : // Throttle MAX
        
        value_ = static_cast<int>(pedal_->throttle_.getData().act);
        break;


        case 8 : // Throttle MIN
        
        value_ = static_cast<int>(pedal_->throttle_.getData().act);
        break;


        case 9 : // Brake MAX
        
        value_ = static_cast<int>(pedal_->brake_.getData().act);
        break;


        case 10 : // Brake MIN
        
        value_ = static_cast<int>(pedal_->brake_.getData().act);
        break;
        

        default:
            
        value_ = 0;
        page_ = 255;
        break;
    }


    if(joyst_->getButtonStatus().pushed && page_ != 255) {
        
        waitForButtonRelease();
        
        // perform action
        
        switch (page_) {
            

            case 0 : // Zero Steering
            
            encoder_->setZero();
            break;


            case 2 : // Rotary X Axis MAX
                     
            eeprom_->put(STORE_ADDR_RX_MAX, joyst_->rotationX_.setMax(AXIS_MAX_PHYSIC));
            break;


            case 3 : // Rotary X Axis MIN
                
            eeprom_->put(STORE_ADDR_RX_MIN, joyst_->rotationX_.setMin(AXIS_MIN_PHYSIC));
            break;


            case 4 : // Rotary Y Axis MAX
                     
            eeprom_->put(STORE_ADDR_RY_MAX, joyst_->rotationY_.setMax(AXIS_MAX_PHYSIC));
            break;


            case 5 : // Rotary Y Axis MIN
                     
            eeprom_->put(STORE_ADDR_RY_MIN, joyst_->rotationY_.setMax(AXIS_MIN_PHYSIC));
            break;


            case 6 : // Steering turn

            eeprom_->put(STORE_ADDR_FACTOR, encoder_->setFactor());
            break;


            case 7 : // Throttle MAX
                
            eeprom_->put(STORE_ADDR_THROTTLE_MAX, pedal_->throttle_.setMaxWithTolerance(AXIS_MAX_PHYSIC, THROTTLE_MAX_ADC_TOLERANCE));
            break;


            case 8 : // Throttle MIN
            
            eeprom_->put(STORE_ADDR_THROTTLE_MIN, pedal_->throttle_.setMinWithTolerance(AXIS_MIN_PHYSIC, THROTTLE_MIN_ADC_TOLERANCE));
            break;


            case 9 : // Brake MAX
            
            eeprom_->put(STORE_ADDR_BRAKE_MAX, pedal_->brake_.setMaxWithTolerance(AXIS_MAX_PHYSIC, BRAKE_MAX_ADC_TOLERANCE));
            break;


            case 10 : // Brake MIN
            
            eeprom_->put(STORE_ADDR_BRAKE_MIN, pedal_->brake_.setMinWithTolerance(AXIS_MIN_PHYSIC, BRAKE_MIN_ADC_TOLERANCE));
            break;


            default:
            
            break;
        }

        page_++;
    }

    // just show pages

    wire_->beginTransmission(LCD_ADDR);
    wire_->write(page_);
    wire_->write((uint8_t*)&value_, sizeof(value_));
    wire_->endTransmission();

}

void SetupDisplay::waitForButtonRelease() {

    while (joyst_->getButtonStatus().pushed){}
}

#endif