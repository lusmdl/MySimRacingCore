#include "SetupDisplay.hpp"

SetupDisplay::SetupDisplay() {

}

SetupDisplay::~SetupDisplay() {

}

void SetupDisplay::begin() {
    
    lcd_ = new LiquidCrystal_I2C(LCD_ADDR, LCD_CHARS, LCD_LINES);


    lcd_->init();
    lcd_->backlight();
    lcd_->setCursor(3,0);
    lcd_->print("Hello, world!");
    
    pageBoot();
}

void SetupDisplay::show() {

}

void SetupDisplay::setNewPage(uint8_t page) {

    page_ = page;
}

void SetupDisplay::pageBoot() {

    // clear everything

    lcd_->clear();
    
    // first line

    lcd_->setCursor(0,0);
    lcd_->print("booting..");

    // second line
    
    lcd_->setCursor(0,1);
    uint8_t wait {0};
    while(wait < 16) {

        lcd_->print(".");
        _delay_ms(100);
        wait++;
    }
    
    
    // first line

    lcd_->setCursor(9,0);
    lcd_->print("success");

}
