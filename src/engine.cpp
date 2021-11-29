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
 * @brief 
 * 
 * @param esc_pin_1 
 * @param esc_pin_2 
 * @param esc_pin_3 
 */
void DCEngine::run_forward(int esc_pin_1, int esc_pin_2, int esc_pin_3) {
    if (this->_backForward == true) {

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
    if (this->_backForward == false) {

    }
}


/**
 * @brief 
 * 
 * @param c 
 */
void DCEngine::message(char c[5]) {
    Serial.println(c);
}