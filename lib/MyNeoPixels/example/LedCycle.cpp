/**
 * @file    LedCycle.cpp
 * @brief   Example program demonstrating the usage of the MyWS2812B library to control WS2812B LEDs.
 * @author  lusmdl
 * @date    05.02.2024
 * 
 * This example initializes a WS2812B strip with 3 LEDs connected to PORTD (PIN6) of the microcontroller.
 * It cycles through red, green, and blue colors on the LEDs in a loop with a delay of 500ms between changes.
 */

#include <MyNeoPixels.hpp>


MyWS2812B leds(DDRD, PORTD, (uint8_t*) _SFR_MEM_ADDR(PORTD), PD6, 3);


int main(void)
{
  leds.clearColor();
  leds.show();

  _delay_ms(2000);

  uint32_t counter;
  while(1)
  {


    uint8_t i_0 = counter % 3;
    uint8_t i_1 = (counter+1) % 3;
    uint8_t i_2 = (counter+2) % 3;

    leds.setColor(i_0, 255, 0 , 0);
    leds.setColor(i_1, 0, 255, 0);
    leds.setColor(i_2, 0, 0, 255);
    leds.show();
    _delay_ms(500);
    counter++;
  }
}
