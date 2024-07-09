
// HEADER
#include "MyButtonMatrix2x2.hpp"


/**
 * @brief the object of the class MyButtonMatrix2x2 with the given parameters.
 * 
 * @param DDXn Reference to the Data Direction Register of the corresponding port
 * @param PORTXn Reference to the Output Register of the corresponding port
 * @param PINXn Reference to the Input Register of the corresponding port
 * @param bit_position Array of bit positions for the button matrix
 * 
 * @warning This method may be unsafe in certain conditions and unexpected behavior could occur.
 * 
 * @note It is important to ensure the correct mapping of bit positions for button matrix functionality.
 * 
 * @example 
 * MyButtonMatrix2x2 matrix(PORTD, PORTD, PIND, {0, 1, 2, 3});
 */
MyButtonMatrix2x2 ::MyButtonMatrix2x2(volatile uint8_t &ddxn, volatile uint8_t &portxn, volatile uint8_t &pinxn, uint8_t bit_position[] ) //: 
  // umbau auf POD struct
  //reg_.ptrDataDirection (&ddxn), 
  //reg_.ptrPort(&portxn), 
  //reg_.ptrPin(&pinxn) 
  //reg_ {&ddxn, &portxn, &pinxn} // gibt probleme
  {
    reg_.ptrDataDirection = &ddxn;
    reg_.ptrPort = &portxn;
    reg_.ptrPin = &pinxn;

  for (uint8_t i = 0; i < BTN_MAX_; i++) {
    
    // init each member
    
    bit_[i] = bit_position[i];
    button_[i].enableInvert = false;
    button_[i].fallingEdge = false;
    button_[i].flagOldPush = false;
    button_[i].numberGetPushed = 0;
    button_[i].pushed = false;
    button_[i].risingEdge = false;
  }
}

MyButtonMatrix2x2 ::MyButtonMatrix2x2(pod_gpioregister& ptr, uint8_t bit_position[BTN_MAX_]) :
  reg_ (ptr) {

    for (uint8_t i = 0; i < BTN_MAX_; i++) {

      // init each member
    
      bit_[i] = bit_position[i];
    }
  }


/**
 * @brief This method returns the status of a button in a 2x2 matrix.
 * 
 * @param button The index of the button
 * @warning This method may behave unpredictably in certain scenarios and is considered unsafe due to potential unspecific behavior.
 * @note Ensure proper connection of the button matrix before calling this method.
 * @example 
 * bool buttonStatus = getButtonStatus(1);
 * if(buttonStatus) {
 *   // Do something
 * } else {
 *   // Do something else
 * }
 */
pod_buttonstatus MyButtonMatrix2x2 ::getButtonStatus(uint8_t button) {  

  uint8_t sense = button % 2;
  uint8_t ground = (button < 2) ? 2 : 3;
  uint8_t live[2] {0,0};

  uint8_t count = 0;

  for (uint8_t i = 0; i < BTN_MAX_; i++) {

    if (i == sense || i == ground) {

      // nothing to see here

    } 
    else {

      live[count] = i;
      count++;  
    }
  }

  setGpioConfig(INPUT_INTERN_PULLUP, *reg_.ptrDataDirection, *reg_.ptrPort, bit_[sense]);
  setGpioConfig(OUTPUT_SINK, *reg_.ptrDataDirection, *reg_.ptrPort, bit_[ground]);
  setGpioConfig(OUTPUT_SOURCE, *reg_.ptrDataDirection, *reg_.ptrPort, bit_[live[0]]);
  setGpioConfig(OUTPUT_SOURCE, *reg_.ptrDataDirection, *reg_.ptrPort, bit_[live[1]]);
  
  execNop();

  // reset edge flags
  
  button_[button].fallingEdge = false;
  button_[button].risingEdge = false;

  // acutal read register data, use this everytime in this method
  bool buttonPushed = getBit(*reg_.ptrPin, bit_[sense]) ? false : true;
  
  if (buttonPushed) {

    button_[button].pushed = true;

    if (button_[button].flagOldPush == false) {

      // rising edge

      button_[button].risingEdge = true;
      button_[button].numberGetPushed++;
    }
  } 
  else {

    button_[button].pushed = false;

    if (button_[button].flagOldPush == true) {

      // falling edge

      button_[button].fallingEdge = true;
    }
  }
  
  // set old flag after
  button_[button].flagOldPush = buttonPushed;
  
  return button_[button];
}

/**
 * @brief Sets the status of the button.
 * 
 * @param value_new The new value for the amount of button numbers pushed (default value is 0)
 * 
 * 
 * 
 * 
*/
pod_buttonstatus MyButtonMatrix2x2 ::setButtonStatus(uint8_t button, uint32_t value_new) {

  button_[button].numberGetPushed = value_new;
  
  if (value_new == 0) {

    // reset everything if new value is zero

    button_[button].pushed = false;
    button_[button].flagOldPush = false;
    button_[button].fallingEdge = false;
    button_[button].risingEdge = false;
  }

  return button_[button];
}