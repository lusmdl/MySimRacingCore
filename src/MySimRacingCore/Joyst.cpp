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
Joyst::Joyst() :
    rotationX(SHIFTER_X_PIN), // Assuming SHIFTER_X_PIN is defined in ProjectConfig.hpp
    rotationY(SHIFTER_Y_PIN)  // Assuming SHIFTER_Y_PIN is defined in ProjectConfig.hpp
{}

/**
 * @brief Destructor for Joyst class.
 */
Joyst::~Joyst() {

}
