
// HEADER
#include "MyButton.hpp"

/**
 * @brief Constructor of the class MyButton
 * Initializes the member variables of the class.
 * 
 * @param PINXn A reference to the register containing the status of the button.
 * @param bit_position The position of the bit in the register representing the button status.
 * @param invert Indicates if the button input should be inverted.
 * 
 * @warning This method may have unforeseen consequences and could be insecure at certain points.
 * 
 * @note Make sure to properly configure the parameters to avoid unexpected behaviors.
 * 
 * @example 
 * MyButton button(pinxn, 3, true);
 */
MyButton ::MyButton(volatile uint8_t &pinxn, uint8_t bit_position, bool invert) : 
  //ptrRegister_(&pinxn), 
  //reg_ {nullptr, nullptr, nullptr}, // gibt probleme wegen der struktur
  bit_ (bit_position), 
  //pushed_(false), 
  //numberGetPushed_(0), 
  //enableInvert_(invert) 
  //button_ {false, false, false, false, 0, invert}, // gibt probleme wegen der struktur
  command_ (nullptr),
  observer_ (nullptr) {

    reg_.ptrPin = &pinxn;
    button_.enableInvert = invert;
  }


/**
 * @brief Constructor of the class MyButton
 * Initializes the member variables of the class.
 * 
 * 
 * 
 * 
*/
MyButton ::MyButton(pod_gpioregister &reg, uint8_t bit_position, bool invert) : 
  reg_(reg),
  bit_(bit_position),
  //button_{false, false, false, false, 0, invert}, // gibt probleme
  command_ (nullptr),
  observer_ (nullptr) {

    
    button_.enableInvert = invert;
  }


/**
 * @brief Returns the status of the button.
 * Checks the state of the button and updates the count of pressed keys.
 * 
 * @param registerPtr Pointer to the register for button status checking
 * @param bit The bit position of the button in the register
 * @param paraInvert Flag for inverting the button status
 * @param numbersGetPushed Number of times the button has been pressed
 * @param pushed Flag indicating if the button is currently pressed
 * 
 * @return The status of the button contained in an POD
 * 
 * @warning This method may have unexpected behavior and is considered unsafe in certain scenarios.
 * 
 * @note Use the parameter paraInvert carefully to handle inverted button status.
 * 
 * @example 
 * bool buttonPushed = getStatus(&register, 3, true, numbersPressed, buttonPressed);
 * if (buttonPushed) {
 *    // Do something if the button is pressed
 * }
 */
pod_buttonstatus MyButton ::getStatus() {

  // this method calculate all data based on the register value
  // WARNING: do not read the calculated values, always read the actual register value

  // Führe eine NOP-Operation für die Synchronisation aus
  execNop();

  // reset edge flags
  
  button_.fallingEdge = false;
  button_.risingEdge = false;

  // acutal read register data, use this everytime in this method
  bool buttonPushed {false};
  
  if (button_.enableInvert) {

    // if the parameter is set, swap the bit
    // this is usefull if you use pullup resistors

    buttonPushed = getBit(*reg_.ptrPin, bit_) ? false : true;
  }
  else {

    buttonPushed = getBit(*reg_.ptrPin, bit_) ? true : false;
  }

  if (buttonPushed) {

    button_.pushed = true;

    if (button_.flagOldPush == false) {

      // rising edge

      button_.risingEdge = true;
      button_.numberGetPushed++;
      if (observer_ != nullptr) {
        
        notifyObserver();
      }
    }
  } 
  else {

    button_.pushed = false;

    if (button_.flagOldPush == true) {

      // falling edge

      button_.fallingEdge = true;
    }
  }

  // set old flag after
  button_.flagOldPush = buttonPushed;

  return button_;
}


/**
 * @brief Sets the status of the button.
 * 
 * @param value_new The new value for the amount of button numbers pushed (default value is 0)
 * 
 * @warning This method may be unsafe in certain scenarios where unexpected behavior could occur.
 * 
 * @note Make sure to handle corner cases carefully when using this method.
 * 
 * @example
 * MyButton myButton;
 * myButton.setStatus(3);
 * // This sets the button status with 3 pushed numbers
 */
void MyButton ::setStatus(uint32_t value_new) {

  button_.numberGetPushed = value_new;
  
  if (value_new == 0) {

    // reset everything if new value is zero

    button_.pushed = false;
    button_.flagOldPush = false;
    button_.fallingEdge = false;
    button_.risingEdge = false;
  }
}


/**
 * 
 * 
 * 
 * 
*/
void MyButton::setCmd(interface_Command *cmd) {

  command_ = cmd;
}

void MyButton::attachObserver(interface_Observer *observer) {

  observer_ = observer;
}

void MyButton::detachObserver(interface_Observer *observer) {

  observer_ = nullptr;
}

void MyButton::notifyObserver() {

  observer_->update("");
}

void MyButton::execCmd() {

  if (command_) {

    command_->exec();
  }
}
