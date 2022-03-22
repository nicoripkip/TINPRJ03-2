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
UltraSoonSensor::UltraSoonSensor(int pin1, int pin2) {
    pinMode(pin1, INPUT);
    pinMode(pin2, OUTPUT);

    this->_pin1 = pin1;
    this->_pin2 = pin2;
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
    digitalWrite(this->_pin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->_pin1, LOW);

    int duration = pulseIn(this->_pin2, HIGH);
    this->setDistance((duration/2) / 29.1);
    
    Serial.print("[info]\tAfstand: ");
    Serial.println(this->getDistance());
}