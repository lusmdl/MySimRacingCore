#ifndef MYBEHAVIORALDESINGPATTERNS_HPP
#define MYBEHAVIORALDESINGPATTERNS_HPP

// HEADER

#include "MyAvr.hpp"


// Observer Design Pattern
// 
// Intent: Lets you define a subscription mechanism to notifyObserver multiple objects
// about any events that happen to the object they're observing.
// 
// Note that there's a lot of different terms with similar meaning associated
// with this pattern. Just remember that the Subject is also called the
// Publisher and the Observer is often called the Subscriber and vice versa.
// Also the verbs "observe", "listen" or "track" usually mean the same thing.


class interface_Observer {

    public:

        // DESTRUCTOR
        virtual ~interface_Observer() {};

        // EXECUTION

        virtual void update(const String &message_from_subject) = 0;
};

class interface_Subject {

    // The Subject owns some important state and notifies observers when the state changes.

    public:

        // DESTRUCTOR
        virtual ~interface_Subject() {};

        // EXECUTION

        virtual void attachObserver(interface_Observer *observer) = 0;
        virtual void detachObserver(interface_Observer *observer) = 0;
        virtual void notifyObserver() = 0;
};



class interface_Command {
    
    // The Command interface declares a method for executing a command.
    // Some commands can implement simple operations on their own.
    
    // class MyCommandExample : public interface_Command {
    // 
    //     public:
    //         virtual void exec() const override {
    //             
    //             // implement code here
    //         }
    // };
    
    public:

        // DESTRUCTOR
        
        virtual ~interface_Command() {};

        // EXECUTION

        virtual void exec() const = 0;
};





#endif // MYBEHAVIORALDESINGPATTERNS_HPP