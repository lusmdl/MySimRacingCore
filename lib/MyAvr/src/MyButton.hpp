#ifndef MYBUTTON_HPP
#define MYBUTTON_HPP

// HEADER

#include "MyAvr.hpp"


class MyButton : 
    private MyController, 
    public interface_Subject {

    private:

        // MEMBER

        // Zeiger auf das Register des Tasters
        pod_gpioregister reg_;
        //volatile uint8_t* ptrRegister_;

        // Bitposition des Tasters im Register
        uint8_t bit_;

        // Tasterstatus (gedrückt oder nicht gedrückt)
        //bool pushed_;
        
        // Anzahl der Tasterbetätigungen
        //uint32_t numberGetPushed_;
        
        // invert the HIGH Signal (usefull if pullup is in use)
        //bool enableInvert_;

        pod_buttonstatus button_;

        // OOP BEHAVIOARAL DESIGN PATTERNS

        // COMMAND

        interface_Command *command_;

        // OBSERVER

        interface_Observer *observer_;

    protected:


    public:

        // CONSTRUCTOR
        
        MyButton(volatile uint8_t &pinxn, uint8_t bit_position, bool invert = false);
        MyButton(pod_gpioregister &reg, uint8_t bit_position, bool invert = false);


        // GETTER

        pod_buttonstatus getStatus();


        // SETTER

        void setStatus(uint32_t value_new = 0);
        void setCmd(interface_Command *cmd);

        // EXECUTE

        // OBSERVER

        virtual void attachObserver(interface_Observer *observer) override;
        virtual void detachObserver(interface_Observer *observer) override;
        virtual void notifyObserver() override;

        // COMMAND

        void execCmd();
};

#endif