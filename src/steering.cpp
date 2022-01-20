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
    ledcWrite(PWM_CHANNEL, 80);
}