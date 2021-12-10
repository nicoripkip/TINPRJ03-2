/**
 * @file steering.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 */


#include <Arduino.h>
#include "./headers/steering.hpp"


/**
 * @brief Construct a new Steering:: Steering object
 * 
 * @param pin 
 */
Steering::Steering(int pin) {
    this->_pin = pin;
}


