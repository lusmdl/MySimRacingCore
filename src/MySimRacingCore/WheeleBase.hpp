#ifndef WHEEL_BASE_HPP
#define WHEEL_BASE_HPP



#include "MySimRacingCore.hpp"

struct pod_forcefeedback
{
    
    //Softlock
    // Definition: Simuliert einen Anschlag am Lenkrad bei maximalem Lenkeinschlag.
    // Funktion: Verhindert, dass das Lenkrad weiter gedreht wird als der eingestellte Winkel.
    // Einstellung: Ein Wert von 0 bis 100%, wobei 100% den maximalen Lenkeinschlag begrenzt.
    uint8_t softlock;


    // Damper
    // Definition: Erzeugt Widerstand basierend auf der Drehgeschwindigkeit des Lenkrads.
    // Funktion: Simuliert die Dämpfung, die bei schnellen Bewegungen des Lenkrads eintritt.
    // Einstellung: Ein Wert von 0 bis 100%, wobei 100% maximale Dämpfung bedeutet.
    uint8_t damper;


    // Friction
    // Definition: Erzeugt konstanten Widerstand gegen das Drehen des Lenkrads.
    // Funktion: Simuliert die Reibung, die bei langsamen Bewegungen des Lenkrads eintritt.
    // Einstellung: Ein Wert von 0 bis 100%, wobei 100% maximale Reibung bedeutet.
    uint8_t friction;


    // Inertia
    // Definition: Erzeugt Widerstand proportional zur Beschleunigung des Lenkrads.
    // Funktion: Simuliert das Trägheitsmoment, das das Lenkrad langsamer werden lässt, wenn es schneller gedreht wird.
    // Einstellung: Ein Wert von 0 bis 100%, wobei 100% maximale Trägheit bedeutet.
    uint8_t inertia;

    int force;

};

/*
struct pod_steering {

    uint8_t maxAngle;
    const double factorAngleDegree {4.235294117647059};
    double maxDegree;
    uint8_t deadzone;
    
    volatile int actEncoderPosition; 
    double actDegree;  
};

class WheelBase {


    public:

        WheelBase();
        void begin();
        void updateForceFeedback();
        void readEncoder();


    private:

        pod_steering datasteering_;
        pod_forcefeedback dataffb_;
        
};

*/


/*
// Example

class ForceFeedbackProcessor {
private:
    Settings settings;
    double maxSteeringAngle; // Maximum steering angle in degrees
    double currentAngle; // Current steering angle
    double previousAngle; // Previous steering angle
    double previousSpeed; // Previous speed of the steering wheel

public:
    ForceFeedbackProcessor(ForceFeedbackSettings settings, float maxSteeringAngle)
        : settings(settings), maxSteeringAngle(maxSteeringAngle), currentAngle(0), previousAngle(0), previousSpeed(0) {}

    void update(float newAngle, float deltaTime) {
        float speed = (newAngle - previousAngle) / deltaTime;
        float acceleration = (speed - previousSpeed) / deltaTime;
        previousAngle = currentAngle;
        currentAngle = newAngle;
        previousSpeed = speed;

        float force = calculateForce(speed, acceleration);
        applyForceToMotor(force);
    }

private:
    float calculateForce(float speed, float acceleration) {
        float force = 0;

        // Softlock
        if (abs(currentAngle) > maxSteeringAngle * settings.softlock / 100.0f) {
            float excessAngle = abs(currentAngle) - maxSteeringAngle * settings.softlock / 100.0f;
            force -= excessAngle * 10; // Softlock stiffness factor
        }

        // Damper
        force -= speed * settings.damper / 100.0f;

        // Friction
        force -= (speed > 0 ? 1 : -1) * settings.friction / 100.0f;

        // Inertia
        force -= acceleration * settings.inertia / 100.0f;

        return force;
    }

    void applyForceToMotor(float force) {
        // Translate the calculated force into motor commands
        std::cout << "Applying force to motor: " << force << std::endl;
        // Here you would convert the force into motor control signals (PWM, etc.)
    }
};





*/


#endif // WHEEL_BASE_HPP
