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


/**
 * @brief Construct a new DCEngine::DCEngine object
 * 
 * @param ESC_PWM_PIN 
 */
DCEngine::DCEngine(int ESC_PWM_PIN) {
    ledcAttachPin(4, PWM_CHANNEL);                    // Zet de ESC pin als PWM pin
    ledcSetup(PWM_CHANNEL, PWM_FREQUENTIE, PWM_RESOLUTION);     // Zet de freq, channel en de resolutie goed voor de pin
}


void DCEngine::arm() {
    int i;
    
    for (i = 0; i < ESC_MAX_ARM_SEQUENCE; i++) {
        ledcWrite(PWM_CHANNEL, ESC_ARM_VALUE);
        delay(200);
    }
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
    ledcWrite(PWM_CHANNEL, 0);
}


/**
 * @brief Functie voor het laten draaien van de motor
 * 
 * @param esc_pin_1 
 * @param esc_pin_2 
 * @param esc_pin_3 
 */
void DCEngine::run_forward() {
    delay(500);

    if (this->_onOff == true) {
        if (this->_backForward == false) {
            ledcWrite(PWM_CHANNEL, this->getSpeed());
        }
    }
}


/**
 * @brief 
 * 
 */
void DCEngine::run_backward() {
    if (this->_onOff == true) {
        if (this->_backForward == true) {
            ledcWrite(PWM_CHANNEL, this->getSpeed());
        }
    }
}


/**
 * @brief Functie voor het zetten van de snelheid
 * 
 * @param speed 
 */
void DCEngine::setSpeed(int speed) {
    this->_speed = speed;
}


/**
 * @brief Functie voor het ophalen van de snelheid
 * 
 * @return double 
 */
int DCEngine::getSpeed() {
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
    this->setAcceleration(0.01);

    // if (this->getSpeed() == NULL) {
    //     this->setSpeed(50); 
    // } 

    if (this->getSpeed() < 255) {
        Serial.print("Versnelling: ");
        Serial.println(this->getSpeed());

        if (this->getSpeed() != 0) {
            this->setSpeed(this->getSpeed() * this->getAcceleration());
        } else {
            this->setSpeed(50);
        }
        
    } else if (this->getSpeed() >= 255) {
        this->setSpeed(50);
    }
}


/**
 * @brief Functie voor het printen van de data van de motor
 * 
 */
void DCEngine::print() {
    Serial.print("Motor status: ");
    Serial.println(this->_onOff);
    Serial.println();
    Serial.print("Motor directie: ");
    Serial.println(this->_backForward);
    Serial.println();
    Serial.print("Snelheid van de motor: ");
    Serial.println(this->getSpeed());
}