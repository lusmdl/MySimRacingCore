#ifndef AXIS_H
#define AXIS_H
/**
 * @file Axis.h
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


// every axis has the same behavior
// this data structur should provide a standard
struct data_axis {
        
    double act; // actual value
    double min; // minimum allowable value
    double max; // maximum allowable value
};
#endif // AXIS_H