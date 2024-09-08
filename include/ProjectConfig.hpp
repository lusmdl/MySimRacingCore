/**
 * @file ProjectConfig.hpp
 * 
 * @brief Definition of Project Pins and other important constatnt Values
 */

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

//#define LUSMDL_DEBUGMODE // activates the debug function of the Serial Monitor 
//#define FFB // activates the force feedback feature

#ifdef LUSMDL_DEBUGMODE
#warning This code is in DEBUG mode!!! The Macro 'LUSMDL_DEBUGMODE' in include/ProjectCofig.hpp has to be comment out
#warning The LCD feature is disabled because of the RAM storage
#endif

// LCD Display

#define LCD_ADDR                0x27
#define LCD_CHARS               16
#define LCD_LINES               2

//I²C Buttons

#define TWI_ADDR_MY_WHEEL_BTN   8
#define TWI_ADDR_MY_BTN_BOX     9


// Pedals

#define THROTTLE_PIN            PINF7 //A0
#define BRAKE_PIN               PINF6 //A1
#define CLUTCH_PIN              PINF5 //A2

// Handbrake

#define HANDBRAKE_PIN           PINF4 //A3 

// Joystick

#define SHIFTER_X_PIN           PINF1 //A4 
#define SHIFTER_Y_PIN           PINF0 //A5
#define JOYSTICK_BTN_PIN        PINB7


// Pin definitions for Button Matrix

#define BTN_MATRIX_L            4   // column
#define BTN_MATRIX_R            4   // row
#define BTN_NUMBER              32  // number of buttons

#define BTN_MATRIX_L1           5   // PC6
#define BTN_MATRIX_L2           6   // PD7
#define BTN_MATRIX_L3           7   // PE6
#define BTN_MATRIX_L4           12  // PD6
#define BTN_MATRIX_R1           14  // SCK
#define BTN_MATRIX_R2           15  // MOSI
#define BTN_MATRIX_R3           16  // MISO
#define BTN_MATRIX_R4           4   // PD4


// Pin definitions for steering encoder (1k ext pullup resistor)

#define ENCODER_A_PIN           0 // D0/TX - don´t edit this !!!!!
#define ENCODER_B_PIN           1 // D1/RX - don´t edit this !!!!!
//#define ENCODER_REG_PIN         PIND


// Force feedback motor control pins

//#define MOTOR_EN_PIN        0   // D8
//#define MOTOR_LPWM_PIN      0   // D9
//#define MOTOR_RPWM_PIN      0   // D10

#endif // PROJECT_CONFIG_H
