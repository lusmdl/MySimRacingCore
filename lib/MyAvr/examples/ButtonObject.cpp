/**
 * Funktion zum Testen eines Mikrocontrollers
 * und zur Konfiguration eines Tasters
 * 
 * @param None
 * 
 * @return None
 */

#include <MyAvr.hpp>

MyAtmega328p myAVR;

int main (void) {

  // teste den Mikrocontroller
  myAVR.execTest(100);

  // initialisiere die UART
  myAVR.initUart(9600);

  // konfiguriere die GPIOs
  myAVR.setGpioConfig(INPUT_INTERN_PULLUP, DDRD, PORTD, PD3);

  MyButton btnTest(PIND, PD3, true);
  
  while (1) {

    // infinity loop

    if (btnTest.getStatus().pushed) {

      // Wenn der Taster gedrückt wird

      myAVR.printUart("btnTest pressed!\n");
      myAVR.execDelayMs(1000);
    }

  }
  return 0;
}