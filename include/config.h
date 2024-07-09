#ifndef CONFIG_H
#define CONFIG_H


// Pin definitions for analog sensors

#define THROTTLE_PIN        //A0
#define BRAKE_PIN           //A1
#define CLUTCH_PIN          //A2
#define HANDBRAKE_PIN       //A3 
#define SHIFTER_X_PIN       //A4 
#define SHIFTER_Y_PIN       //A5


// Pin definitions for digital sensors (buttons)

#define BTN_MATRIX_A_L1     0 //D5
#define BTN_MATRIX_A_L2     0 //D6
#define BTN_MATRIX_A_R1     0 //D14
#define BTN_MATRIX_A_R2     0 //D15
#define BTN_MATRIX_A_DDR    DDRD
#define BTN_MATRIX_A_PORT   PORTD
#define BTN_MATRIX_A_PIN    PIND

#define BTN_MATRIX_B_L1     0 //D7
#define BTN_MATRIX_B_L2     0 //D12
#define BTN_MATRIX_B_R1     0 //D14
#define BTN_MATRIX_B_R2     0 //D15
#define BTN_MATRIX_B_DDR    DDRD
#define BTN_MATRIX_B_PORT   PORTD
#define BTN_MATRIX_B_PIN    PIND

#define BTN_MATRIX_C_L1     0 //D5
#define BTN_MATRIX_C_L2     0 //D6
#define BTN_MATRIX_C_R1     0 //D16
#define BTN_MATRIX_C_R2     0 //D4
#define BTN_MATRIX_C_DDR    DDRD
#define BTN_MATRIX_C_PORT   PORTD
#define BTN_MATRIX_C_PIN    PIND

#define BTN_MATRIX_D_L1     0 //D7
#define BTN_MATRIX_D_L2     0 //D12
#define BTN_MATRIX_D_R1     0 //D16
#define BTN_MATRIX_D_R2     0 //D4
#define BTN_MATRIX_D_DDR    DDRD
#define BTN_MATRIX_D_PORT   PORTD
#define BTN_MATRIX_D_PIN    PIND

// Pin definitions for steering encoder (1k ext pullup resistor)
#define ENCODER_A_PIN       // D0
#define ENCODER_B_PIN       // D1

// Force feedback motor control pins

#define MOTOR_EN_PIN        //D8
#define MOTOR_LPWM_PIN      //D9
#define MOTOR_RPWM_PIN      //D10

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


#endif // CONFIG_H
