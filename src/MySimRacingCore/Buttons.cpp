#include "Buttons.hpp"


Buttons::Buttons() : 
    rowpins_{BTN_MATRIX_R1, BTN_MATRIX_R2, BTN_MATRIX_R3, BTN_MATRIX_R4},
    columnspins_{BTN_MATRIX_L1, BTN_MATRIX_L2, BTN_MATRIX_L3, BTN_MATRIX_L4},
    keyarray_{ // make shure the alphabet is correct
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

    keys_.setDebounceTime(10);
}

void Buttons::listener() {
    // Abfragen und Verarbeiten von Tastendrücken
    
    char eventKey = keys_.getKey();
    
    #ifdef LSMDL_DEBUGMODE
    if (eventKey) {

        Serial.print("Key Pressed Event at key " + String(eventKey) + "\n");
    }
    #endif
    
    // only one key can be pressed at each cycle!

    switch (keys_.getState()) {
        case PRESSED:
            // Handle pressed event

            //data_[].pushed++; 

            break;
        case RELEASED:
            // Handle released event

            //data_[mapalphabet_[eventKey]].pushed = 0;

            break;
    }

    
}
