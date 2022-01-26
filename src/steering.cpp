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
    ledcAttachPin(this->_pin, PWM_CHANNEL);
    ledcSetup(PWM_CHANNEL, PWM_FREQUENTIE, PWM_RESOLUTION);
}


/**
 * @brief Functie voor het instellen van de snelheid
 * 
 * @param speed 
 */
void Steering::setSpeed(int speed) {
    this->_speed = speed;
}


/**
 * @brief Functie voor het ophalen van de snelheid
 * 
 * @return int 
 */
int Steering::getSpeed() {
    return this->_speed;
}


/**
 * @brief Functie voor het zetten van de servo status
 * 
 * @param state 
 */
void Steering::setState(int state) {
    this->_servo_state = state;
}


/**
 * @brief Functie voor het ophalen van de servo status
 * 
 * @return int 
 */
int Steering::getState() {
    return this->_servo_state;
}


/**
 * @brief Functie voor het instellen hoeveel graden de motor moet draaien
 * 
 * @param degree 
 */
void Steering::setTurnDegree(int degree) {

}


/**
 * @brief Functie voor het ophalen van het aantal stuurgraden
 * 
 * @return int 
 */
int Steering::getTurnDegree() {

}


/**
 * @brief Functie voor het naar links sturen van de servo
 * 
 */
void Steering::turnLeft() {
    Serial.println("Draai naar links!");
    ledcWrite(PWM_CHANNEL, this->getSpeed()); // Max value 30
    delay(50);
}


/**
 * @brief Functie voor het naar rechts sturen van de servo
 * 
 */
void Steering::turnRight() {
    Serial.println("Draai naar rechts!");
    ledcWrite(PWM_CHANNEL, this->getSpeed()); // Min value 10
    delay(50);
}


/**
 * @brief Functie voor het zetten van het nulpunt
 * 
 */
void Steering::setZeroPoint() {
    switch (this->getState())
    {
        case LEFT:
            this->turnRight();
        break;
        case RIGHT:
            this->turnLeft();
        break;
    }
}