#ifndef MYNEOPIXELS_HPP
#define MYNEOPIXELS_HPP

// AVR

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// MACROS

#define TIME_RESET 50 // WS2812 and clones only need 50 µs


// ENUMS

/**
 * @brief Predesigned color, where you can choose from
 * 
 * @note 
    RED,
    BLUE,
    YELLOW,
    GREEN,
    ORANGE,
    PURPLE,
    PINK,
    BROWN,
    BLACK,
    WHITE,   
    WARM_WHITE
 * 
 * 
 * 
*/
enum enum_colormodes {
    
    RED,
    BLUE,
    YELLOW,
    GREEN,
    ORANGE,
    PURPLE,
    PINK,
    BROWN,
    BLACK,
    WHITE,   
    WARM_WHITE

};


/**
 * @brief mapping of the color values
 * 
 * 
 * @note
    RGB,
    RBG,
    GRB,
    GBR,
    BGR,
    BRG
 * 
*/
enum enum_colormapping {
    RGB,
    RBG,
    GRB,
    GBR,
    BGR,
    BRG
};


// Plain Old Data
//
// Für Datenübertragung zwischen Softwarekomponenten
// 
// Regeln:
// - Einfache Datenstrukturen
// - Nur Daten, keine Methoden
// - kompakt und leichtgewichtig
// - portabel
// - unveränderlich

/**
 * @brief Structure of the LED array
 *
 * @note RGB  for WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
 */
struct pod_rgb  { 

    uint8_t g; 
    uint8_t r; 
    uint8_t b; 
};

/**
 * @brief Structure of the LED array
 *
 * @note RGBW for SK6812RGBW
 */
struct pod_rgbw { 
    
    uint8_t g; 
    uint8_t r; 
    uint8_t b; 
    uint8_t w;
};

/**
 * @brief this structure contains all informations about the led array
 * 
 * @warning the color values are in a diffrent container
 * 
*/
struct pod_leddata {

    uint8_t maxNumberOfLeds;
    uint8_t *brightness;
};



// CLASSES 

// BASIC CLASS

/**
 * @brief the basic class for all kind of LED Strings
 * 
 * 
 * @note contains common data and methods
 * 
 * 
 * 
*/
class MyNeoPixels {

    protected:

        // MEMBER

        // CONSTANTS

        // Brightness values, adapted to the actual brightness curve from 0 to 255
        static const uint8_t DIM_CURVE[256];
};

// NEO PIXEL TYPES

#include "MyWS2812B.hpp"

#endif