/**
 * @file    ButtonMatrix2x2.cpp
 * @brief   Example program demonstrating the usage of 2x2 button matrix.
 * @author  lusmdl
 * @date    06.02.2024
 * 
 * This is an example of an application with 2x2 button matrix.
 * During the code, one pin is configured to input with pullup resistor
 * One pin is configured as output sink to form the ground.
 * the other two pins are set to output high to avoid interference.
 * 
 * In the example, the matrix was connected as follows:
 * L1 -> PD2
 * L2 -> PD3
 * R1 -> PD4
 * R2 -> PD5
 */


#include <MyAvr.hpp>


MyAtmega328p myAVR;

int main(void)
{
  
  myAVR.execTest(100);

  myAVR.initUart(9600);

  // config button matrix
  uint8_t matrixPins[] {PD2, PD3, PD4, PD5};
  MyButtonMatrix2x2 btnMatrix(DDRD, PORTD, PIND, matrixPins);


  while (1)
  {
  /* code */
  
  myAVR.printUart("\nBEGIN\n");

  for ( int i = 0; i < 4; i++)
  {
    myAVR.printUart ("button #" + String(i) + ": " +  String(btnMatrix.getButtonStatus(i).pushed) + "\n");
  
  }
    myAVR.execDelayMs(1000);
  }
  return 0;
}