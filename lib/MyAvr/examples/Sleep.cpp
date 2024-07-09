/*

In diesem Programmstück wird auf die AVR-Bibliothek MyAVR zugegriffen, 
um einen Atmega328p-Mikrocontroller zu initialisieren und einzuschalten. 
Zunächst wird ein Objekt namens 'myAtmega328p' erstellt, 
welches den Mikrocontroller repräsentiert und die CPU-Frequenz auf 8 MHz gesetzt wird. 
Anschließend wird eine LED an den Pin PD4 angeschlossen und als Ausgang konfiguriert, 
um sie später anschalten zu können.

Dann wird die LED mit der Methode 'setBit' eingeschaltet, 
indem sie auf HIGH gesetzt wird. Danach wird der Atmega328p in den Stromsparmodus Power Save versetzt (sleep), 
um Energie zu sparen. Dabei wird das PRTIM0-Bit im PRR-Register gesetzt, um den Timer/Counter 0 zu deaktivieren. 
Die Methode 'sleep' setzt auch die benötigten Bits im SMCR-Register, um den Atmega328p in den Power Save-Modus zu bringen.

Während der Atmega328p im Stromsparmodus ist, wird das Programm pausiert und die LED bleibt eingeschaltet, 
bis der Atmega328p aufwacht.

Wenn der Atmega328p aufwacht, wird die while-Schleife aufgerufen. Darin wird zuerst die LED ausgeschaltet, 
indem das entsprechende Bit im PORTD-Register auf LOW gesetzt wird. Der Code verbleibt dann in der Schleife, 
wobei das Wechseln des Stromsparmodus manuell durch das Drücken des Resettasters angestoßen werden kann.

*/




#include <MyAvr.hpp>



MyAtmega328p myAVR;

int main(void)
{
  
  // teste den Mikrocontroller
  myAVR.execTest(100);

  // initialisiere die UART
  myAVR.initUart(9600);

  // LED an Pin PD4 anschließen und als Ausgang konfigurieren
  myAVR.setGpioConfig(OUTPUT_SOURCE, DDRD, PORTD, PD4);

  // LED einschalten
  myAVR.setBit(PORTD, PD4, true);

  myAVR.printUart("enter sleepmode\n");
  myAVR.execDelayMs(1000);

  // In den Power Save Modus wechseln
  myAVR.execSleep(POWER_SAVE, (1 << PRTIM0), false);
  

  // Programm pausiert hier, bis der Atmega328p aufwacht

  while (1) {

  
    myAVR.printUart("loop\n");
  }
  return 0;
}