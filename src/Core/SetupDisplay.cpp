#include "SetupDisplay.hpp"
#ifndef LUSMDL_DEBUGMODE


SetupDisplay::SetupDisplay(Joyst &joyst, Encoder &encoder):
    joyst_(&joyst),
    encoder_(&encoder),
    page_(0)
{}


SetupDisplay::~SetupDisplay() {}


void SetupDisplay::begin() {
    
    lcd_ = new LiquidCrystal_I2C(LCD_ADDR, LCD_CHARS, LCD_LINES);

    lcd_->init();
    lcd_->backlight();
    printLine(0, TXT_TEST_MSG);
}


bool SetupDisplay::runSetup() {

    switch (page_) {

        case 0 : // ask user, if want´s to make setup wizard
            if(askForSetup()) {

                // begin with wizard

                clearLine(0);
                clearLine(1);
                
                page_++;
            }
            else {

                // no setup needed
                return 0;
            }
            break;

        case 1 : // Rotary X Axis
            setupRxMax();            
            break;

        case 2 : // Rotary X Axis
            setupRxMin();
            break;

        case 3 : // Rotary Y Axis
            setupRyMax();            
            break;

        case 4 : // Rotary Y Axis
            setupRyMin();
            break;

        case 5 :
            setupSteeringZero();
            break;

        case 6 :
            setupSteeringTurn();
            break;

        case 7 :
            printLine(1,String(encoder_->getData().act));
            break;

        default:

            printLine(0,TXT_FAIL);
            return 0;
            break;
    }
    return 1;
}


bool SetupDisplay::askForSetup() {

    // clear everything

    printLine(0, TXT_BOOTING);

    // loading bar

    uint8_t wait {0};
    lcd_->setCursor(0,1);
    while(wait < LCD_CHARS) {

        if (joyst_->getButtonStatus().pushed) {

            // run setup wizard

            waitForButtonRelease();

            return true; // feedback, that the user want´s to run the setup wizard
        }
        
        lcd_->print(".");
        _delay_ms(200);
        wait++;
    }
    
    // end

    lcd_->clear();
    lcd_->setCursor(0,0);
    #ifndef LUSMDL_DEBUGMODE
    lcd_->print(TXT_BOOT_DONE);
    #endif
    #ifdef LUSMDL_DEBUGMODE
    lcd_->print(TXT_DEBUG);
    #endif

    _delay_ms(500);

    lcd_->noBacklight();
    lcd_->clear();

    return false; // feedback, that no setup wizard is needed
}


void SetupDisplay::clearLine(uint8_t line) {

    lcd_->setCursor(0,line);
    lcd_->print(TXT_CLEAR);
}


void SetupDisplay::printLine(uint8_t line, String txt) {

    /*
    lcd_->setCursor(0, line);
    lcd_->print(TXT_CLEAR);  
    lcd_->setCursor(0, line);
    lcd_->print(txt); 
    */

    lcd_->setCursor(0, line);
    String data = txt.substring(0, LCD_CHARS); // truncate to 16 characters if longer
    while (data.length() < LCD_CHARS) { // pad with spaces if shorter
        data += " ";
    }
    lcd_->print(data);
}



void SetupDisplay::waitForButtonRelease() {

    while (joyst_->getButtonStatus().pushed){}
}

void SetupDisplay::setupRxMax() {

    if(joyst_->getButtonStatus().pushed) {

        waitForButtonRelease();
        
        printLine(0, TXT_DONE);
        printLine(1, String(joyst_->rotationX_.getData().act));
        joyst_->rotationX_.setMaxHere(100.00);

        _delay_ms(500);
        
        clearLine(0);
        clearLine(1);

        page_++;
    }
    else {

        lcd_->setCursor(0,0);
        lcd_->print("set Rx Max");
        printLine(1, String(joyst_->rotationX_.getData().act));
    }
}

void SetupDisplay::setupRxMin() {

    if(joyst_->getButtonStatus().pushed) {

        waitForButtonRelease();
        

        printLine(0, TXT_DONE);
        printLine(1, String(joyst_->rotationX_.getData().act));
        joyst_->rotationX_.setMinHere(00.00);

        _delay_ms(500);
        
        clearLine(0);
        clearLine(1);

        page_++;
    }
    else {

        lcd_->setCursor(0,0);
        lcd_->print("set Rx Min");
        printLine(1, String(joyst_->rotationX_.getData().act));
    }
}

void SetupDisplay::setupRyMax() {

    if(joyst_->getButtonStatus().pushed) {

        waitForButtonRelease();
        
        printLine(0, TXT_DONE);
        printLine(1, String(joyst_->rotationY_.getData().act));
        joyst_->rotationY_.setMaxHere(100.00);

        _delay_ms(500);
        
        clearLine(0);
        clearLine(1);

        page_++;
    }
    else {

        lcd_->setCursor(0,0);
        lcd_->print("set Ry Max");
        lcd_->setCursor(0,1);
        printLine(1, String(joyst_->rotationY_.getData().act));
    }
}

void SetupDisplay::setupRyMin() {

    if(joyst_->getButtonStatus().pushed) {

        waitForButtonRelease();
        

        printLine(0, TXT_DONE);
        printLine(1, String(joyst_->rotationY_.getData().act));
        joyst_->rotationY_.setMinHere(00.00);

        _delay_ms(500);
        
        clearLine(0);
        clearLine(1);

        page_++;
    }
    else {

        lcd_->setCursor(0,0);
        lcd_->print("set Ry Min");
        printLine(1, String(joyst_->rotationY_.getData().act));
    }
}

void SetupDisplay::setupSteeringZero() {

    if(joyst_->getButtonStatus().pushed) {

        waitForButtonRelease();
        
        printLine(0, TXT_DONE);
        printLine(1, String(encoder_->getPosition()));
        encoder_->setZeroHere();

        _delay_ms(500);
        
        clearLine(0);
        clearLine(1);

        page_++;
    }
    else {

        lcd_->setCursor(0,0);
        lcd_->print("set wheel 0");
        printLine(1, String(encoder_->getPosition()));
    }
}

void SetupDisplay::setupSteeringTurn() {

    if(joyst_->getButtonStatus().pushed) {

        waitForButtonRelease();
        
        printLine(0, TXT_DONE);
        printLine(1, String(encoder_->getPosition()));
        encoder_->setFullTurnHere();

        _delay_ms(500);
        
        clearLine(0);
        clearLine(1);

        page_++;
    }
    else {

        lcd_->setCursor(0,0);
        lcd_->print("set wheel 360 deg");
        printLine(1, String(encoder_->getPosition()));
    }
}

#endif