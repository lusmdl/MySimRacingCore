/**
 * @file    TimeCounter.cpp
 * @brief   Example program demonstrating the usage of timer 0.
 * @author  lusmdl
 * @date    09.02.2024
 * 
 * This code is a microcontroller program written in C++ for an Atmega328p microcontroller. 
 * The program sets up a timer interrupt on Timer0 which is triggered every 1ms. 
 * Inside the interrupt handler, the variables for milliseconds, seconds, minutes, 
 * and hours are incremented accordingly to keep track of time. 
 * 
 * The main function initializes the microcontroller, sets up UART communication, 
 * configures Timer0 with the correct values for a 1ms interrupt, and then enters 
 * a loop where the current time is printed to the UART every second using the updated variables. 
 * 
 * Overall, this program demonstrates how to use interrupts and timers on an Atmega328p 
 * microcontroller to keep track of time accurately at the millisecond level.
 */


#include <MyAvr.hpp>


//Variablen für die Zeit
volatile unsigned int millisekunden;
volatile unsigned int sekunde;
volatile unsigned int minute;
volatile unsigned int stunde;

/*
Der Compare Interrupt Handler 
wird aufgerufen, wenn 
TCNT0 = OCR0A = 125-1 
ist (125 Schritte), d.h. genau alle 1 ms
*/
ISR (TIMER0_COMPA_vect)
{
  millisekunden++;
  if(millisekunden == 1000)
  {
    sekunde++;
    millisekunden = 0;
    if(sekunde == 60)
    {
      minute++;
      sekunde = 0;
    }
    if(minute == 60)
    {
      stunde++;
      minute = 0;
    }
    if(stunde == 24)
    {
      stunde = 0;
    }
  }
}

MyAtmega328p myAVR;

int main(void) {
  
  myAVR.execTest(100);

  myAVR.initUart(9600);

  // init timer0

  /**
   * 
   * 
   * 
   * 
   * 
   * calculation
   * F_CPU= 8 Mhz
   * 
   * 8.000.000 / 64(prescaler) = 125.000 
   * 125.000 / 1000 = 125
   * 125 -1 = 124 (compare value if the quarz is perfect in time)
   * 
   * 
   * 
  */ 
  myAVR.setTC0Config(CTC, CLK_64, 124);


  while (1) {
    
    myAVR.printUart("\n----------\nBEGIN LOOP\n");
    myAVR.printUart("millis:\t" + String(millisekunden) + "\nsec:\t" + String(sekunde) + "\nminute:\t" + String(minute) + "\nhour:\t" + String(stunde) + "\n");
    myAVR.execDelayMs(1000);
  }

  return 0;
}