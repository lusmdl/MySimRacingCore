/**
 * @file    PoliceLight.cpp
 * @brief   Example program demonstrating the usage of the MyWS2812B library to control WS2812B LEDs.
 * @author  lusmdl
 * @date    08.02.2024
 * 
 * This C++ function utilizes the "MyNeoPixels.hpp" library to control NeoPixel LEDs, 
 * mimicking a flashing police light effect. It initializes the LEDs with red and blue colors, 
 * switching between them to create a flashing sequence. 
 * 
 * The brightness is adjusted gradually during the process to enhance the flashing effect, 
 * and the function continues this sequence repeatedly until the program is stopped.
 * 
 */

#include <MyNeoPixels.hpp>

#define PARA_WAIT 2 // milliseconds

MyWS2812B leds(DDRD, PORTD, (uint8_t*) _SFR_MEM_ADDR(PORTD), PD6, 3);




int main(void)
{
  leds.clearColor();
  
  leds.show();

  _delay_ms(2000);


  uint8_t mode {0};

  while(1)
  {
    uint8_t led1;
    uint8_t led2;
    uint8_t led3;
    leds.setBrightness(255);
    for (uint16_t i = 0; i < 3; i++)
    {
      leds.setColor(i, 255,0,0);
    }

    switch ((mode%2))
    {
    case 0:
      
      led1 = 0;
      led2 = 1;
      led3 = 2;
      

      break;

    case 1:
      
      led3 = 0;
      led1 = 1;
      led2 = 2;
      

      break;
    
    default:
      break;
    }
    

    leds.setColor(led1, 0,0,255);
    leds.setColor(led2, 0,0,255);
    leds.setColor(led3, 255,0,0);
    for (uint16_t i = 0; i < 4; i++)
    {
      // blue
      leds.setBrightness(255, led3);
      for (int j = 255; j > 0; j-=8)
      {
        leds.setBrightness(j,led1);
        leds.setBrightness(j,led2);
        leds.show();
        _delay_ms(PARA_WAIT);
      }
      
      // red
      leds.setBrightness(255,led1);
      leds.setBrightness(255,led2);
      for (int j = 255; j > 0; j-=8)
      {
        leds.setBrightness(j,led3);
        leds.show();
        _delay_ms(PARA_WAIT);
      }
    }
    mode ++;
  }
}
