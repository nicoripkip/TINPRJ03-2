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


#define ESC_PIN_1 0x03
#define ESC_PIN_2 0x04
#define ESC_PIN_3 0x05

#define IR_SENSOR_PIN_1 0x07
#define IR_SENSOR_PIN_2 0x08
#define IR_SENSOR_PIN_3 0x09
#define IR_SENSOR_PIN_4 0x0A
#define IR_SENSOR_PIN_5 0x0B
#define IR_SENSOR_PIN_6 0x0C


void initialize_content();


/**
 * @brief Functie die alles opzet 
 * 
 */
void setup() {
  initialize_content();

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
  // Declareer objecten
  DCEngine engine;


  // Declareer pinModes
  engine.init_spi_ports(ESC_PIN_1, ESC_PIN_2, ESC_PIN_3);
}