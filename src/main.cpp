/** ===========================================================================================
 * @file main.cpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#include <Arduino.h>
#include "./headers/communication.hpp"
#include "./headers/engine.hpp"


/**
 * @brief Functie die alles opzet 
 * 
 */
void setup() {
  Serial.begin(115200);
}


/**
 * @brief Functie die continue loopt
 * 
 */
void loop() {
  // put your main code here, to run repeatedly:
}


/**
 * @brief Functie voor het initialiseren van alle
 *        belangrijke dingen
 * 
 */
void initialize_content()
{
  DCEngine engine;
  engine.start();
}