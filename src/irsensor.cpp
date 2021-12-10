/** ===========================================================================================
 * @file irsensor.cpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#include <Arduino.h>
#include "./headers/irsensor.hpp"
#include "./headers/sensors.hpp"


/**
 * @brief Construct a new IRSensor::IRSensor object
 * 
 */
IRSensor::IRSensor(int pin) {
    this->setPin(pin);
}


/**
 * @brief Functie voor het zetten van de afstand 
 * 
 * @param distance 
 */
void IRSensor::setDistance(double distance) {
    this->_distance = distance;
}


/**
 * @brief Functie voor het teruggeven van de afstand
 * 
 * @return int 
 */
double IRSensor::getDistance() {
    return this->_distance;
}


/**
 * @brief Functie voor het bepalen of de sensor een lijn detecteerd of niet
 * 
 * @return true 
 * @return false 
 */
bool IRSensor::crossedLine() {
    if (this->getActive() == LOW) {
        return true;
    }
    
    return false;
}


void IRSensor::print() {
    int x = digitalRead(this->getPin());

    Serial.print("Output IR: ");
    Serial.println(x);

    delay(500);
}