#include "SetupDisplay.hpp"
//#ifndef LUSMDL_DEBUGMODE

SetupDisplay::SetupDisplay(Joyst &joyst):
    joyst_(&joyst),
    page_(0)
{}

SetupDisplay::~SetupDisplay() {}


void SetupDisplay::begin() {
    
    lcd_ = new LiquidCrystal_I2C(LCD_ADDR, LCD_CHARS, LCD_LINES);

    lcd_->init();
    lcd_->backlight();
    lcd_->setCursor(3,0);
    lcd_->print("Hello, world!");
    
}

bool SetupDisplay::runSetup() {

    lcd_->clear();

    switch (page_) {

        case 0 : 
            if(askForSetup()) {
                page_++;
            }
            else {

                // no setup needed
                return 0;
            }
            break;

        default:
            lcd_->setCursor(0,0);
            lcd_->print("unknown page");
            return 0;
            break;
    }
    return 1;
}

void SetupDisplay::setNewPage(uint8_t page) {

    page_ = page;
}

bool SetupDisplay::askForSetup() {

    // clear everything

    lcd_->setCursor(0,0);
    lcd_->print("booting..");
    lcd_->setCursor(0,1);

    uint8_t wait {0};
    while(wait < 16) {

        if (joyst_->getButtonStatus().pushed) {

            return true;
        }
        
        lcd_->print(".");
        _delay_ms(200);
        wait++;
    }
    
    
    // end

    lcd_->clear();
    lcd_->setCursor(0,0);
    #ifndef LUSMDL_DEBUGMODE
    lcd_->print("booting..success");
    #endif
    #ifdef LUSMDL_DEBUGMODE
    lcd_->print("debug mode");
    #endif

    _delay_ms(500);
    lcd_->noBacklight();
    lcd_->clear();
    return false;

}
//#endif