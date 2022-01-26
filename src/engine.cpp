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
 * @param motor1_pin1 
 * @param motor1_pin2 
 * @param motor2_pin1 
 * @param motor2_pin2 
 */
DCEngine::DCEngine(int motor1_pin1, int motor1_pin2, int motor2_pin1, int motor2_pin2) 
{
    this->set_motor1_pin1(motor1_pin1);
    this->set_motor1_pin2(motor1_pin2);
    this->set_motor2_pin1(motor2_pin1);
    this->set_motor2_pin2(motor2_pin2);

    pinMode(this->get_motor1_pin1(), OUTPUT);
    pinMode(this->get_motor1_pin2(), OUTPUT);
    pinMode(this->get_motor2_pin1(), OUTPUT);
    pinMode(this->get_motor2_pin2(), OUTPUT);
}


/**
 * @brief Functie om de motor aan te zetten
 * 
 */
void DCEngine::start()
{
    if (this->get_life_state() == false) {
        this->set_life_state(true);
    }
}


/**
 * @brief Functie om de motor uit te zetten
 * 
 */
void DCEngine::stop()
{
    if (this->get_life_state() == true) {
        this->set_life_state(false);

        digitalWrite(this->get_motor1_pin1(), LOW);
        digitalWrite(this->get_motor1_pin2(), LOW);
        digitalWrite(this->get_motor2_pin1(), LOW);
        digitalWrite(this->get_motor2_pin2(), LOW);
    }
}


/**
 * @brief Functie voor het vooruit laten draaien van de motor
 * 
 */
void DCEngine::run_forward()
{
    if (this->get_life_state() == false) {
        Serial.println("[error]\tDe motor moet nog eerst gestart worden!");
        return;
    }

    if (this->get_moving_state() == RUN_FORWARD) {
        digitalWrite(this->get_motor1_pin1(), HIGH);
        digitalWrite(this->get_motor1_pin2(), LOW);
        digitalWrite(this->get_motor2_pin1(), HIGH);
        digitalWrite(this->get_motor2_pin2(), LOW);
    }
}


/**
 * @brief Functie voor het achteruit laten draaien van de motor
 * 
 */
void DCEngine::run_backward()
{
    if (this->get_life_state() == false) {
        Serial.println("[error]\tDe motor moet nog eerst gestart worden!");
        return;
    }

    if (this->get_moving_state() == RUN_BACKWARD) {
        digitalWrite(this->get_motor1_pin1(), LOW);
        digitalWrite(this->get_motor1_pin2(), HIGH);
        digitalWrite(this->get_motor2_pin1(), LOW);
        digitalWrite(this->get_motor2_pin2(), HIGH);
    }
}


/**
 * @brief Functie voor het printen van gegevens van de motor 
 * 
 */
void DCEngine::print()
{
    Serial.println("[info]\tGegevens van de motor!");
    Serial.println();
    Serial.print("[info]\tMotorstatus: ");
    Serial.println(this->get_life_state());
    Serial.print("[info]\tRichting van draaien: ");
    Serial.println(this->get_moving_state());
}


/**
 * @brief Functie voor het zetten van motor 1 pin 1
 * 
 * @param pin 
 */
void DCEngine::set_motor1_pin1(int pin)
{
    this->_motor1_pin1 = pin;
}


/**
 * @brief Functie voor het ophalen van motor 1 pin 1
 * 
 * @return int 
 */
int DCEngine::get_motor1_pin1()
{
    return this->_motor1_pin1;
}


/**
 * @brief Functie voor het zetten van motor 1 pin 2
 * 
 * @param pin 
 */
void DCEngine::set_motor1_pin2(int pin)
{
    this->_motor1_pin2 = pin;
}


/**
 * @brief Functie voor het ophalen van motor 1 pin 2
 * 
 * @return int 
 */
int DCEngine::get_motor1_pin2()
{
    return this->_motor1_pin2;
}


/**
 * @brief Functie voor het zetten van motor 2 pin 1
 * 
 * @param pin 
 */
void DCEngine::set_motor2_pin1(int pin)
{
    this->_motor2_pin1 = pin;
}


/**
 * @brief Functie voor het ophalen van motor 2 pin 1
 * 
 * @return int 
 */
int DCEngine::get_motor2_pin1()
{
    return this->_motor2_pin1;
}


/**
 * @brief Functie voor het zetten van motor 2 pin 2
 * 
 * @param pin 
 */
void DCEngine::set_motor2_pin2(int pin)
{
    this->_motor2_pin2 = pin;
}


/**
 * @brief Functie voor het ophalen van motor 2 pin 2
 * 
 * @return int 
 */
int DCEngine::get_motor2_pin2()
{
    return this->_motor2_pin2;   
}


/**
 * @brief Functie voor het zetten van de levensstaat
 * 
 * @param state 
 */
void DCEngine::set_life_state(bool state)
{
    this->_life_state = state;
}


/**
 * @brief Functie voor het ophalen van de levensstaat
 * 
 * @return true 
 * @return false 
 */
bool DCEngine::get_life_state()
{
    return this->_life_state;
}


/**
 * @brief Functie voor het zetten van de beweginsstaat
 * 
 * @param state 
 */
void DCEngine::set_moving_state(int state)
{
    this->_moving_state = state;
}


/**
 * @brief Functie voor het ophalen van de moving state
 * 
 * @return true 
 * @return false 
 */
int DCEngine::get_moving_state()
{
    return this->_moving_state;
}