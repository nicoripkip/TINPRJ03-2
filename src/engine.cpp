/** ===========================================================================================
 * @file engine.cpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#include <Arduino.h>
#include "headers/engine.hpp"


DCEngine::DCEngine(int ESC_PWM_PIN) {
    ledcSetup(PWM_CHANNEL, PWM_FREQUENTIE, PWM_RESOLUTION);
    ledcAttachPin(ESC_PWM_PIN, PWM_CHANNEL);
}


/**
 * @brief Functie voor het declareren van de motor pinnen
 * 
 * @param esc_pin_1 
 * @param esc_pin_2 
 * @param esc_pin_3 
 */
void DCEngine::init_spi_ports(int esc_pin_1, int esc_pin_2, int esc_pin_3) {
    pinMode(esc_pin_1, OUTPUT);
    pinMode(esc_pin_2, OUTPUT);
    pinMode(esc_pin_3, OUTPUT);
}


/**
 * @brief Functie voor het starten van de motor
 * 
 */
void DCEngine::start() {
    this->_onOff = true;
}


/**
 * @brief Functie voor het stoppen van de motor
 * 
 */
void DCEngine::stop() {
    this->_onOff = false;
}


/**
 * @brief Functie voor het laten draaien van de motor
 * 
 * @param esc_pin_1 
 * @param esc_pin_2 
 * @param esc_pin_3 
 */
void DCEngine::run_forward(int esc_pin_1, int esc_pin_2, int esc_pin_3) {
    if (this->_onOff == true) {
        if (this->_backForward == true) {
            ledcWrite(esc_pin_2, this->getSpeed());
        }
    }
}


/**
 * @brief 
 * 
 * @param esc_pin_1 
 * @param esc_pin_2 
 * @param esc_pin_3 
 */
void DCEngine::run_backward(int esc_pin_1, int esc_pin_2, int esc_pin_3) {
    if (this->_onOff == true) {
        if (this->_backForward == false) {

        }
    }
}


/**
 * @brief Functie voor het zetten van de snelheid
 * 
 * @param speed 
 */
void DCEngine::setSpeed(double speed) {
    this->_speed = speed;
}


/**
 * @brief Functie voor het ophalen van de snelheid
 * 
 * @return double 
 */
double DCEngine::getSpeed() {
    return this->_speed;
}


/**
 * @brief Functie voor het zetten van de versnelling
 * 
 * @param multiplier 
 */
void DCEngine::setAcceleration(double multiplier) {
    this->_multiplier = multiplier;
}


/**
 * @brief Functie voor het ophalen van de versnelling
 * 
 * @return double 
 */
double DCEngine::getAcceleration() {
    return this->_multiplier;
}


/**
 * @brief Functie voor het versnellen van de motor
 * 
 */
void DCEngine::accelerate() {
    if (this->getSpeed() == NULL) {
        this->setSpeed(0.0); 
    } else {
        this->setSpeed(this->getSpeed());
    }

    if (this->getSpeed() < 255) {
        this->setSpeed(this->getSpeed() * this->getAcceleration());
    } else if (this->getSpeed() >= 255) {
        this->setSpeed(255);
    }
}