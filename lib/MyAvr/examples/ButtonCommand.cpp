/**
 * @file ButtonCommand.cpp
 * @brief Funktion zum Testen eines Mikrocontrollers
 * und zur Konfiguration eines Tasters
 * 
 * @warning not tested yet!!!!!!!!!!!!
 * 
 * @date 28.03.2024
 * @author lusmdl
 */

#include <MyAvr.hpp>

MyAtmega328p myAVR;


class CommandExample : public interface_Command {

    

  public:

    virtual void exec() const override {

      myAVR.printUart("btnTest pressed!\n");
      myAVR.execDelayMs(1000);
    }
};


class ObserverExample : public interface_Observer {

  private:

    CommandExample *command_;

  public:

    ObserverExample (CommandExample *cmd) : command_ (cmd) {}

    virtual void update(const String &message_from_subject) override {

      myAVR.printUart(message_from_subject);

      command_->exec();
    }
};

int main (void) {

  // teste den Mikrocontroller
  myAVR.execTest(100);

  // initialisiere die UART
  myAVR.initUart(9600);

  // konfiguriere die GPIOs
  myAVR.setGpioConfig(INPUT_INTERN_PULLUP, DDRD, PORTD, PD3);

  // Button object
  MyButton btnTest(PIND, PD3, true);

  // command
  CommandExample cmdExample;

  // observer
  // connect command with the observer
  ObserverExample obsExample(&cmdExample);

  // connect the command and observer with the button object
  btnTest.setCmd(&cmdExample);
  btnTest.attachObserver(&obsExample);
  
  while (1) {

    // infinity loop

    btnTest.getStatus();
  }
  return 0;
}