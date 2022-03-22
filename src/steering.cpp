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
void Steering::turnLeft(int speed) {
    Serial.println("Draai naar links!");
    this->setSpeed(speed); // default 27
    this->setState(LEFT);
    ledcWrite(PWM_CHANNEL, this->getSpeed()); // Max value 30
    delay(50);
}


/**
 * @brief Functie voor het naar rechts sturen van de servo
 * 
 */
void Steering::turnRight(int speed) {
    Serial.println("Draai naar rechts!");
    this->setSpeed(speed); // default 17
    this->setState(RIGHT);
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
        // Als de voorwielen naar links gedraait staan
        case LEFT:
            this->setState(MIDDLE);
            this->turnRight(22);
        break;
        // Als de voorwielen naar rechts gedraait staan
        case RIGHT:
            this->setState(MIDDLE);
            this->turnLeft(22);
        break;
        // Als de voorwielen gecentreerd staan
        case MIDDLE:
            return;
        break;
    }
}