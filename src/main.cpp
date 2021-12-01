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
#include "./headers/irsensor.hpp"


#define ESC_PIN_1 0x03
#define ESC_PIN_2 0x04
#define ESC_PIN_3 0x05

#define IR_SENSOR_PIN_1 0x07
#define IR_SENSOR_PIN_2 0x08
#define IR_SENSOR_PIN_3 0x09
#define IR_SENSOR_PIN_4 0x0A
#define IR_SENSOR_PIN_5 0x0B
#define IR_SENSOR_PIN_6 0x0C


// Declareer objecten
DCEngine engine(ESC_PIN_2); // Maakt een object aan voor de motor
IRSensor sensor1(IR_SENSOR_PIN_1); // Kijkt voor een lijn voor de ACM
IRSensor sensor2(IR_SENSOR_PIN_2); // Kijkt voor een lijn achter de ACM
IRSensor sensor3(IR_SENSOR_PIN_3); // Kijkt voor een lijn aan de linkerkant voor van de ACM
IRSensor sensor4(IR_SENSOR_PIN_4); // Kijkt voor een lijn aan de linkerkant achter van de ACM
IRSensor sensor5(IR_SENSOR_PIN_5); // Kijkt voor een lijn aan de rechterkant voor van de ACM
IRSensor sensor6(IR_SENSOR_PIN_6); // Kijkt voor een lijn aan de rechterkant achter van de ACM


void initialize_content();


/**
 * @brief Functie die alles opzet 
 * 
 */
void setup() {
  // Declareer pinModes
  engine.init_spi_ports(ESC_PIN_1, ESC_PIN_2, ESC_PIN_3);

  // Initialiseer communicatie
  Serial.begin(115200);
}


/**
 * @brief Functie die continue loopt
 * 
 */
void loop() {
  if (sensor1.crossedLine()) {
    engine.stop();
    delay(2000);
    engine.run_backward(ESC_PIN_1, ESC_PIN_2, ESC_PIN_3);
  } else if (sensor2.crossedLine()) {
    engine.stop();
    delay(2000);
    engine.run_forward(ESC_PIN_1, ESC_PIN_2, ESC_PIN_3);
  } else if (sensor1.crossedLine() && sensor2.crossedLine()) {
    engine.stop();
  }
}