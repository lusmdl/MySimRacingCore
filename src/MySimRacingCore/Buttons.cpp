#include "Buttons.hpp"


Buttons::Buttons() : 
    rowpins_{BTN_MATRIX_R1, BTN_MATRIX_R2, BTN_MATRIX_R3, BTN_MATRIX_R4},
    columnspins_{BTN_MATRIX_L1, BTN_MATRIX_L2, BTN_MATRIX_L3, BTN_MATRIX_L4},
    keyarray_{
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'L'},
        {'M', 'N', 'O', 'P'}
    },
    keys_(makeKeymap(keyarray_), rowpins_, columnspins_, BTN_MATRIX_R, BTN_MATRIX_L)
    
{}

Buttons::~Buttons() {
    // Keine dynamische Speicherfreigabe erforderlich
}

void Buttons::begin() {
    // Initialisieren der Keypad- oder Hardware-Komponenten
}

void Buttons::listener() {
    // Abfragen und Verarbeiten von Tastendrücken
    
    char keyPressed = keys_.getKey();
    if (keyPressed) {
        
        #ifdef LSMDL_DEBUGMODE
        Serial.print("Key Pressed Event at key ");
        Serial.println(keyPressed);
        #endif
        
        char k = 'A'; // for the mapping to my pod_buttonmatrix
        for (uint8_t i = 0; i < BTN_NUMBER; i++) {

            // check if the tag of the key matches

            if (k == keyPressed) {

                // when match increase the pushed counter

                data_[i].pushed++;
                
                #ifdef LSMDL_DEBUGMODE
                Serial.print("inc pod_button ");
                Serial.println(String(i));
                #endif  
            }

            // don´t forget to increase the letter
            k++; 
        }
    }
}