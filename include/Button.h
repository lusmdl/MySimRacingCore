/**
 * @file ButtonMatrix.h
 * 
 * @brief Definition of data structures for managing button matrix states.
 * 
 * This header file defines the data structures like `pod_button` which represents
 * the state of buttons in a matrix. These data structures facilitate module
 * interchangeability and are used to ensure smooth data transfer between software modules.
 * 
 * This interface ensures that modules can be swapped seamlessly by providing a
 * standardized way to manage button matrix states across different software components.
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <stdint-gcc.h>

/// @brief Defines the state of a button in a matrix.
struct pod_button {

    uint8_t pushed; // Indicates whether the button was pushed (>= 1) or not (0).
};

#endif