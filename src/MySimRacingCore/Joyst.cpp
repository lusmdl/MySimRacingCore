/**
 * @file Joyst.cpp
 * @brief Implementation of the Joyst class.
 */ 

#include "Joyst.hpp"

/**
 * @brief Constructor for Joyst class.
 * 
 * Initializes the rotationX and rotationY ADCAxis objects.
 */
Joyst::Joyst() {

    rotationX = new ADCAxis(SHIFTER_X_PIN); // Assuming pin 0 for X-axis
    rotationY = new ADCAxis(SHIFTER_Y_PIN); // Assuming pin 1 for Y-axis
}

/**
 * @brief Destructor for Joyst class.
 * 
 * Cleans up the allocated ADCAxis objects.
 */
Joyst::~Joyst() {

    delete rotationX;
    delete rotationY;
}
