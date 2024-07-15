/**
 * @file ProjectConfig.hpp
 * 
 * @brief Definition of Project Pins and other important constatnt Values
 */

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

//#define LSMDL_DEBUGMODE // activates the debug function of the Serial Monitor 

#ifdef LSMDL_DEBUGMODE
#warning "This code is in DEBUG mode!!! The Macro 'LSMDL_DEBUGMODE' in include/ProjectCofig.hpp has to be comment out"
#warning "The LCD feature is disabled because of the RAM storage
#endif

// LCD Display
#define LCD_ADDR            0x27
#define LCD_CHARS           16
#define LCD_LINES           2


// Pin definitions for analog sensors

#define THROTTLE_PIN        0   //A0
#define BRAKE_PIN           0   //A1
#define CLUTCH_PIN          0   //A2
#define HANDBRAKE_PIN       0   //A3 
#define SHIFTER_X_PIN       PF1 //A4 
#define SHIFTER_Y_PIN       PF0 //A5


// Pin definitions for Button Matrix

#define BTN_MATRIX_L        4   // column
#define BTN_MATRIX_R        4   // row
#define BTN_NUMBER          32  // number of buttons

#define BTN_MATRIX_L1       5   // PC6
#define BTN_MATRIX_L2       6   // PD7
#define BTN_MATRIX_L3       7   // PE6
#define BTN_MATRIX_L4       12  // PD6
#define BTN_MATRIX_R1       14  // SCK
#define BTN_MATRIX_R2       15  // MOSI
#define BTN_MATRIX_R3       16  // MISO
#define BTN_MATRIX_R4       4   // PD4


// Pin definitions for steering encoder (1k ext pullup resistor)

#define ENCODER_A_PIN       PD2 // D0/TX
#define ENCODER_B_PIN       PD3 // D1/RX


// Force feedback motor control pins

#define MOTOR_EN_PIN        0   // D8
#define MOTOR_LPWM_PIN      0   // D9
#define MOTOR_RPWM_PIN      0   // D10



// EEPROM addresses to store settings

#define EEPROM_ADDR_MAX_ANGLE           0x00
#define EEPROM_ADDR_DEADZONE            0x08

#define EEPROM_ADDR_THROTTLE_MIN        0x10
#define EEPROM_ADDR_THROTTLE_MAX        0x18
#define EEPROM_ADDR_BRAKE_MIN           0x20
#define EEPROM_ADDR_BREAKE_MAX          0x28
#define EEPROM_ADDR_CLUTCH_MIN          0x30
#define EEPROM_ADDR_CLUTCH_MAX          0x38
#define EEPROM_ADDR_HANDBRAKE_MIN       0x40
#define EEPROM_ADDR_HANDBRAKE_MAX       0x48

#define EEPROM_ADDR_THORTTLE_ACTIVE     0x50
#define EEPROM_ADDR_BRAKE_ACTIVE        0x58
#define EEPROM_ADDR_CLUTCH_ACTIVE       0x60
#define EEPROM_ADDR_HANDBRAKE_ACTIVE    0x68

#define EEPROM_ADDR_FFB_SOFTLOCK        0x70
#define EEPROM_ADDR_FFB_DAMPER          0x78
#define EEPROM_ADDR_FFB_FRICTION        0x80
#define EEPROM_ADDR_FFB_INERTIA         0x88

#define EEPROM_ADDR_ENC_INC             0x90


#endif // PROJECT_CONFIG_H
