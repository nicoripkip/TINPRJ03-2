/** ===========================================================================================
 * @file sensors.cpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#include <Arduino.h>
#include "./headers/sensors.hpp"


/**
 * @brief Construct a new Sensor:: Sensor object
 * 
 */
Sensor::Sensor() {
    this->setPinMode();
}


/**
 * @brief Functie voor het zetten van de waarde of het actief
 *        is of niet
 * 
 * @param active 
 */
void Sensor::setActive(int active) {
    this->_active = active;
}


/**
 * @brief Functie voor het ophalen van de waarde
 * 
 * @return int 
 */
int Sensor::getActive() {
    return this->_active;
}


/**
 * @brief Functie voor het defineren van de pin
 * 
 * @param pin 
 */
void Sensor::setPin(int pin) {
    this->_pin = pin;
}


/**
 * @brief Functie voor het ophalen van de pin
 * 
 * @return int 
 */
int Sensor::getPin() {
    return this->_pin;
}


/**
 * @brief Functie voor het defineren van de pin
 * 
 */
void Sensor::setPinMode() {
    pinMode(this->getPin(), INPUT);
}