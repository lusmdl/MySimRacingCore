#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H


// Pin definitions for analog sensors

#define THROTTLE_PIN        0//A0
#define BRAKE_PIN           0//A1
#define CLUTCH_PIN          0//A2
#define HANDBRAKE_PIN       0//A3 
#define SHIFTER_X_PIN       0//A4 
#define SHIFTER_Y_PIN       0//A5


// Pin definitions for digital sensors (buttons)

#define BTN_NUMBER          16 // number of buttons

#define BTN_MATRIX_A_L1     PB0 // RXLED/SS (R7 must be removed)
#define BTN_MATRIX_A_L2     PB1 // SCK
#define BTN_MATRIX_A_R1     PB2 // MOSI
#define BTN_MATRIX_A_R2     PB3 // MISO
#define BTN_MATRIX_A_DDR    DDRB
#define BTN_MATRIX_A_PORT   PORTB
#define BTN_MATRIX_A_PIN    PIND

#define BTN_MATRIX_B_L1     PB4 // IO8
#define BTN_MATRIX_B_L2     PB5 // IO9
#define BTN_MATRIX_B_R1     PB2 // MOSI
#define BTN_MATRIX_B_R2     PB3 // MISO
#define BTN_MATRIX_B_DDR    DDRB
#define BTN_MATRIX_B_PORT   PORTB
#define BTN_MATRIX_B_PIN    PIND

#define BTN_MATRIX_C_L1     PB0 // RXLED/SS (R7 must be removed)
#define BTN_MATRIX_C_L2     PB1 // SCK
#define BTN_MATRIX_C_R1     PB6 // IO10
#define BTN_MATRIX_C_R2     PB7 // IO11
#define BTN_MATRIX_C_DDR    DDRB
#define BTN_MATRIX_C_PORT   PORTB
#define BTN_MATRIX_C_PIN    PINB

#define BTN_MATRIX_D_L1     PB4 // IO8
#define BTN_MATRIX_D_L2     PB5 // IO9
#define BTN_MATRIX_D_R1     PB6 // IO10
#define BTN_MATRIX_D_R2     PB7 // IO11
#define BTN_MATRIX_D_DDR    DDRB
#define BTN_MATRIX_D_PORT   PORTB
#define BTN_MATRIX_D_PIN    PINB

// Pin definitions for steering encoder (1k ext pullup resistor)
#define ENCODER_A_PIN       PD0 // D0/TX
#define ENCODER_B_PIN       PD1 // D1/RX

// Force feedback motor control pins

#define MOTOR_EN_PIN        0//D8
#define MOTOR_LPWM_PIN      0//D9
#define MOTOR_RPWM_PIN      0//D10

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
