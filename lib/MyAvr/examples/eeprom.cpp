/**
 * @file    Eeprom.cpp
 * @brief   Example program demonstrating the usage of the EEPROM.
 * @author  lusmdl
 * @date    06.02.2024
 * 
 * Verwenden Sie die Methoden `writeToEEPROM()` und `readFromEEPROM()`, 
 * um den Wert einer ganzen Zahl in den EEPROM-Speicher zu schreiben 
 * bzw. aus dem EEPROM-Speicher zu lesen.
 */

#include <MyAvr.hpp>



MyAtmega328p myAVR;

int value = myAVR.readFromEEPROM(0x10);


int main(void) {

  // teste den Mikrocontroller
  myAVR.execTest(100);

  // initialisiere die UART
  myAVR.initUart(9600);

  // konfiguriere die GPIOs
  myAVR.setGpioConfig(INPUT_PULLUP, DDRD, PORTD, PD3);

  MyButton btnTest(PIND, PD3, true);

  




  while (1) {

    // Lese den Wert von Adresse 0x10 aus dem EEPROM
    myAVR.printUart(String(myAVR.readFromEEPROM(0x10)) + "\n");



    if (btnTest.getStatus().pushed)
    {
      /* Wenn der Taster gedrückt wird */
      myAVR.execDelayMs(1000);
      myAVR.printUart("btnTest pressed!\n");

      value++;

      // Schreibe den Wert 42 an Adresse 0x10
      myAVR.writeToEEPROM(0x10, value);

    }

  }
  return 0;
}