#include "Buttons.hpp"


Buttons::Buttons() : 
    rowpins_{BTN_MATRIX_R1, BTN_MATRIX_R2, BTN_MATRIX_R3, BTN_MATRIX_R4},
    columnspins_{BTN_MATRIX_L1, BTN_MATRIX_L2, BTN_MATRIX_L3, BTN_MATRIX_L4},
    keyarray_{ // the getmap method make shure the key names are correct
        {getmap(0),     getmap(1),  getmap(2),      getmap(3)},
        {getmap(4),     getmap(5),  getmap(6),      getmap(7)},
        {getmap(8),     getmap(9),  getmap(10),     getmap(11)},
        {getmap(12),    getmap(13), getmap(14),     getmap(15)}
    },
    keys_(makeKeymap(keyarray_), rowpins_, columnspins_, BTN_MATRIX_R, BTN_MATRIX_L),
    lasteventkey_('\0')
{}

Buttons::~Buttons() {
    // Keine dynamische Speicherfreigabe erforderlich
}

void Buttons::begin() {

    // Initialisieren der Keypad- oder Hardware-Komponenten

    keys_.setDebounceTime(1);
    keys_.setHoldTime(1);
}

void Buttons::listener() {
    // Abfragen und Verarbeiten von Tastendrücken
    
    char eventKey = keys_.getKey(); // nessesarry to get the data for the other methods
    
    #ifdef LSMDL_DEBUGMODE
    if (eventKey) {

        Serial.print("Key Pressed Event at key " + String(eventKey) + "\n");
        lasteventkey_ = eventKey;
    }
    #endif

    #ifdef LSMDL_DEBUGMODE
    if (keys_.keyStateChanged()){
        
        Serial.print("Key state change at key " + String(lasteventkey_) + "\n");
    }
    #endif

    // only one key can be pressed at each cycle!

    switch (keys_.getState()) {
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
        default: return 255; // Rückgabe eines ungültigen Werts für nicht definierte Tasten
    }
}


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
        default: return '\0'; // Rückgabe eines Nullzeichens für ungültige Indizes
    }
}

