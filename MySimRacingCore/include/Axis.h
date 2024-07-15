/**
 * @file Axis.hpp
 * 
 * @brief Definition of data structures for managing axis values.
 * 
 * This header file defines the data structures like `data_axis` which provides a standard
 * representation for axis properties.
 * 
 * These data structures facilitate uniform behavior across axes and ensure consistent
 * handling of axis-related data within software modules.
 * 
 */

#ifndef AXIS_H
#define AXIS_H

/// @brief every axis has the same behavior. this data structur should provide a standard
struct pod_axis {
        
    float act; // actual value
    float min; // minimum allowable value
    float max; // maximum allowable value
};

#endif