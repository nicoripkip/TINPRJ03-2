/** ===========================================================================================
 * @file ultrasoonsensor.cpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021- 01 - 14
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#include "headers/ultrasoonsensor.hpp"


/**
 * @brief Construct a new Ultra Soon Sensor:: Ultra Soon Sensor object
 * 
 * @param pin 
 */
UltraSoonSensor::UltraSoonSensor(int pin) {
    pinMode(pin, INPUT);
}


/**
 * @brief Methode voor het ophalen van de afstand
 * 
 * @return int 
 */
int UltraSoonSensor::getDistance() {
    return this->_distance;
}


/**
 * @brief Methode voor het
 * 
 * @param distance int
 */
void UltraSoonSensor::setDistance(int distance) {
    this->_distance = distance;
}


/**
 * @brief Methode voor het detecteren van een obstakel
 * 
 * @return true 
 * @return false 
 */
bool UltraSoonSensor::detectObstacle() {
    if (this->getDistance() <= 20) {
        return true;
    }

    return false;
}