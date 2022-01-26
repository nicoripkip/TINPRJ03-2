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
#include "./headers/steering.hpp"


#define REED_PIN 0x01

#define MOTOR1_PIN1 32
#define MOTOR1_PIN2 35
#define MOTOR2_PIN1 0
#define MOTOR2_PIN2 4

#define IR_SENSOR_PIN_1 0x07
#define IR_SENSOR_PIN_2 0x08
#define IR_SENSOR_PIN_3 0x09
#define IR_SENSOR_PIN_4 0x0A
#define IR_SENSOR_PIN_5 0x0B
#define IR_SENSOR_PIN_6 0x10

#define ULTRASOON_PIN_1 0x0E
#define ULTRASOON_PIN_2 0x0F

#define ACCELEROMETER_PIN 0x11
#define GYRO_PIN 0x12

#define SERVO_PIN 0x17


// Declareer objecten
DCEngine engine(MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2);           // Maakt een object aan voor de motor
IRSensor sensor1(IR_SENSOR_PIN_1);    // Kijkt voor een lijn voor de ACM
IRSensor sensor2(IR_SENSOR_PIN_2);    // Kijkt voor een lijn achter de ACM
IRSensor sensor3(IR_SENSOR_PIN_3);    // Kijkt voor een lijn aan de linkerkant voor van de ACM
IRSensor sensor4(IR_SENSOR_PIN_4);    // Kijkt voor een lijn aan de linkerkant achter van de ACM
IRSensor sensor5(IR_SENSOR_PIN_5);    // Kijkt voor een lijn aan de rechterkant voor van de ACM
IRSensor sensor6(IR_SENSOR_PIN_6);    // Kijkt voor een lijn aan de rechterkant achter van de ACM
Steering steering(SERVO_PIN);         // Object voor het 0------------------------------------------


/**
 * @brief Functie die alles opzet 
 * 
 */
void setup() {
  engine.start();
  steering.setSpeed(80);
  Serial.begin(9600);
}


/**
 * @brief Functie die continue loopt
 * 
 */
void loop() {
  sensor6.print();
  sensor6.capture();

  engine.set_moving_state(1);
  engine.run_forward();

  engine.print();
  steering.setSpeed(30);
  steering.turnLeft();
  delay(3000);
  steering.setSpeed(10);
  steering.turnRight();
  delay(500);
} 