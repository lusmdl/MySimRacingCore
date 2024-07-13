/**
 * @file Buttons.cpp
 * @brief Implementation of the Buttons class.
 */

#include "Buttons.hpp"

/**
 * @brief Constructor for Buttons class.
 * 
 * Initializes the row and column pins, key array, and keypad object.
 */
Buttons::Buttons() :
    rowpins_{BTN_MATRIX_R1, BTN_MATRIX_R2, BTN_MATRIX_R3, BTN_MATRIX_R4},
    columnspins_{BTN_MATRIX_L1, BTN_MATRIX_L2, BTN_MATRIX_L3, BTN_MATRIX_L4},
    keyarray_{ // The getmap method ensures the key names are correct
        {getmap(0),     getmap(1),  getmap(2),      getmap(3)},
        {getmap(4),     getmap(5),  getmap(6),      getmap(7)},
        {getmap(8),     getmap(9),  getmap(10),     getmap(11)},
        {getmap(12),    getmap(13), getmap(14),     getmap(15)}
    },
    keys_(makeKeymap(keyarray_), rowpins_, columnspins_, BTN_MATRIX_R, BTN_MATRIX_L),
    lasteventkey_('\0')
{}

/**
 * @brief Destructor for Buttons class.
 * 
 * No dynamic memory allocation is required.
 */
Buttons::~Buttons() {
    // No dynamic memory allocation required
}

/**
 * @brief Initializes the keypad or hardware components.
 */
void Buttons::begin() {
    keys_.setDebounceTime(1);
    keys_.setHoldTime(1);
}

/**
 * @brief Listens and processes key presses.
 * 
 * Polls the keypad and processes key press events. Updates the data_ array with key press counts.
 */
void Buttons::listener() {

    // Poll and process key presses
    
    char eventKey = keys_.getKey(); // Necessary to get the data for the other methods
    
    if (eventKey) {
        #ifdef LSMDL_DEBUGMODE
        Serial.print("Key Pressed Event at key " + String(eventKey) + "\n");
        #endif
        lasteventkey_ = eventKey;
    }

    #ifdef LSMDL_DEBUGMODE
    if (keys_.keyStateChanged()) {
        Serial.print("Key state change at key " + String(lasteventkey_) + "\n");
    }
    #endif


    switch (keys_.getState()) { // Only one key can be pressed at each cycle!!

        case PRESSED:
            // Handle pressed event
            
            #ifdef LSMDL_DEBUGMODE
            Serial.print("key state PRESSED at key " + String(lasteventkey_) + " old value was " + String(data_[getmap(lasteventkey_)].pushed));
            #endif

            data_[getmap(lasteventkey_)].pushed++; 
            
            #ifdef LSMDL_DEBUGMODE
            Serial.print(" and the new value is " + String(data_[getmap(lasteventkey_)].pushed) + "\n");
            #endif

            break;
        case RELEASED:
            // Handle released event

            #ifdef LSMDL_DEBUGMODE
            Serial.print("key state RELEASED at key " + String(lasteventkey_) + " old value was " + String(data_[getmap(lasteventkey_)].pushed));
            #endif

            data_[getmap(lasteventkey_)].pushed = 0; 

            #ifdef LSMDL_DEBUGMODE
            Serial.print(" and the new value is " + String(data_[getmap(lasteventkey_)].pushed) + "\n");
            #endif

            break;
    }
}

/**
 * @brief Gets the data of a specific button.
 * 
 * @param button The button index.
 * @return pod_button The data of the specified button.
 */
pod_button Buttons::getData(uint8_t button) {

    return data_[button];
}

/**
 * @brief Maps a character key to an integer index.
 * 
 * @param key The character key.
 * @return int The integer index corresponding to the key.
 */
int Buttons::getmap(char key) {

    switch (key) {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 6;
        case 'H': return 7;
        case 'I': return 8;
        case 'J': return 9;
        case 'K': return 10;
        case 'L': return 11;
        case 'M': return 12;
        case 'N': return 13;
        case 'O': return 14;
        case 'P': return 15;
        default: return 255; // Return an invalid value for undefined keys
    }
}

/**
 * @brief Maps an integer index to a character key.
 * 
 * @param key The integer index.
 * @return char The character key corresponding to the index.
 */
char Buttons::getmap(int key) {

    switch (key) {
        case 0: return 'A';
        case 1: return 'B';
        case 2: return 'C';
        case 3: return 'D';
        case 4: return 'E';
        case 5: return 'F';
        case 6: return 'G';
        case 7: return 'H';
        case 8: return 'I';
        case 9: return 'J';
        case 10: return 'K';
        case 11: return 'L';
        case 12: return 'M';
        case 13: return 'N';
        case 14: return 'O';
        case 15: return 'P';
        default: return '\0'; // Return a null character for invalid indices
    }
}
