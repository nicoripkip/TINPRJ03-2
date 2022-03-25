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
#include "./headers/ultrasoonsensor.hpp"


#define   REED_PIN              23

#define   MOTOR1_PIN1           32
#define   MOTOR1_PIN2           19
#define   MOTOR2_PIN1           2
#define   MOTOR2_PIN2           4

#define   IR_SENSOR_PIN_1       22
#define   IR_SENSOR_PIN_2       21
#define   IR_SENSOR_PIN_3       17
#define   IR_SENSOR_PIN_4       27

#define   ULTRASOON_PIN_1       15
#define   ULTRASOON_PIN_2       12

#define   SERVO_PIN             5


void controller(); 
void check_running_state(int);
void detect_line();
void detect_object();
void detect_checkpoint();


// Declareer objecten
DCEngine engine(MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2);           // Maakt een object aan voor de motor
IRSensor sensor1(IR_SENSOR_PIN_1);    // Kijkt voor een lijn voor de ACM
IRSensor sensor2(IR_SENSOR_PIN_2);    // Kijkt voor een lijn achter de ACM
IRSensor sensor3(IR_SENSOR_PIN_3);    // Kijkt voor een lijn aan de linkerkant voor van de ACM
IRSensor sensor4(IR_SENSOR_PIN_4);    // Kijkt voor een lijn aan de linkerkant achter van de ACM
Steering steering(SERVO_PIN);         // Object voor het sturen
UltraSoonSensor soon1(ULTRASOON_PIN_1, ULTRASOON_PIN_2);


int activate_state = 1;
volatile bool engine_state = true;
volatile bool front_detected = false;
volatile bool back_detected = false;

volatile unsigned short _sensor1;
volatile unsigned short _sensor2;
volatile unsigned short _sensor3;
volatile unsigned short _sensor4;


/**
 * @brief Functie die alles opzet 
 * 
 */
void setup() 
{
  Serial.begin(9600);
  wifi_init();
  
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN_1), detect_line, FALLING);
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN_2), detect_line, FALLING);
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN_3), detect_line, FALLING);
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN_4), detect_line, FALLING);
  attachInterrupt(digitalPinToInterrupt(REED_PIN), detect_checkpoint, CHANGE);

  steering.setZeroPoint();
  delay(1000);
}


/**
 * @brief Functie die continue loopt
 * 
 */
void loop() 
{
  _sensor1 = digitalRead(IR_SENSOR_PIN_1);
  _sensor2 = digitalRead(IR_SENSOR_PIN_2);
  _sensor3 = digitalRead(IR_SENSOR_PIN_3);
  _sensor4 = digitalRead(IR_SENSOR_PIN_4);

  digitalWrite(12, HIGH);

  detect_object();

  engine.set_moving_state(1);

  if (engine_state == false && front_detected == true && back_detected == false) {
    engine.stop();
    delay(2000);
    steering.setZeroPoint();
    engine.start();
    engine.set_moving_state(2);

    if (_sensor2 != 0 && _sensor1 == 0) {
      steering.turnRight(17);
    } else if (_sensor1 != 0 && _sensor2 == 0) {
      steering.turnLeft(27);
    } else {
      unsigned short number = random(0, 300);

      if (number <= 149) {
        steering.turnLeft(27);
      } else if (number >= 150) {
        steering.turnRight(17);
      }
    }

    engine.run_backward();
    delay(800);
    steering.setZeroPoint();
    engine.set_moving_state(1);
    engine.run_forward();

    engine_state = true;
    front_detected = false;
    back_detected = false;
  } else if (engine_state == false && back_detected == true && front_detected == false) {
    engine.stop();
    delay(2000);
    steering.setZeroPoint();
    engine.start();
    engine.set_moving_state(1);

    if (_sensor4 != 0 && _sensor3 == 0) {
      steering.turnRight(17);
    } else if (_sensor3 != 0 && _sensor4 == 0) {
      steering.turnLeft(27);
    } else {
      steering.setZeroPoint();
    }

    engine.run_forward();
    delay(800);
    steering.setZeroPoint();
    engine.set_moving_state(2);
    engine.run_backward();

    engine_state = true;
    front_detected = false;
    back_detected = false;
  }

  switch (engine_state) {
    case true:
      engine.start();
    break;
    case false:
      engine.stop();
    break;
  }
}


/**
 * @brief 
 * 
 */
void detect_line()
{
  noInterrupts();

  _sensor1 = digitalRead(IR_SENSOR_PIN_1);
  _sensor2 = digitalRead(IR_SENSOR_PIN_2);
  _sensor3 = digitalRead(IR_SENSOR_PIN_3);
  _sensor4 = digitalRead(IR_SENSOR_PIN_4);

  // Rechtsboven
  if (_sensor1 != 0) {          // Rechtsboven
    engine_state = false;
    front_detected = true;
    back_detected = false;
  } else if (_sensor2 != 0) {  // Linksboven
    engine_state = false;
    front_detected = true;
    back_detected = false;
  } else if (_sensor3 != 0) { // Rechtsonder
    engine_state = false;
    back_detected = true;
    front_detected = false;
  } else if (_sensor4 != 0) { // linksonder
    engine_state = false;
    back_detected = true;
    front_detected = false;
  }

  interrupts();
}


/**
 * @brief Functie voor het detecteren van een magneet
 * 
 */
void detect_checkpoint()
{
  engine_state = false;
  front_detected = false;
  back_detected = false;
}


/**
 * @brief Functie voor het besturen van de auto
 * 
 */
void controller() 
{
  String response_left = get_left();
  String response_right = get_right();
  String response_up = get_up();
  String response_down = get_down();
  String response_activate = get_activate();

  Serial.println(response_activate);

  DynamicJsonDocument document_left(2048);
  DynamicJsonDocument document_right(2048);
  DynamicJsonDocument document_up(2048);
  DynamicJsonDocument document_down(2048);
  DynamicJsonDocument document_activate(2048);

  DeserializationError error_left = deserializeJson(document_left, response_left);
  DeserializationError error_right = deserializeJson(document_right, response_right);
  DeserializationError error_up = deserializeJson(document_up, response_up);
  DeserializationError error_down = deserializeJson(document_down, response_down);
  DeserializationError error_activate = deserializeJson(document_activate, response_activate);
  
  if (error_left || error_right || error_up || error_down || error_activate) {
      Serial.println("[error]\tJson kan niet worden omgezet!");
  }

  uint8_t left = document_left["value"].as<int>();
  uint8_t right = document_right["value"].as<int>();
  uint8_t up = document_up["value"].as<int>();
  uint8_t down = document_down["value"].as<int>();

  activate_state = document_activate["value"].as<int>();

  check_running_state(document_activate["value"].as<int>());

  if (up != 0 && down == 0) {
    Serial.println("[succes]\tACM rijdt vooruit!");
    engine.set_moving_state(1);
    engine.run_forward();
  } else if (up == 0 && down != 0) {
    Serial.println("[succes]\tACM rijdt achteruit!");
    engine.set_moving_state(2);
    engine.run_backward();
  } else {
    Serial.println("[error]\t\tACM staat stil!");
    engine.stop();
  }

  if (left != 0 && right == 0) {
    steering.turnLeft(27);
  } else if (left == 0 && right != 0) {
    steering.turnRight(17);
  } else if (left == 0 && right == 0) {
    steering.setZeroPoint();
  } else {
    // steering.setZeroPoint();
  }
}


/**
 * @brief Functie om te kijken of de ACM kan rijden
 * 
 */
void check_running_state(int state)
{
  switch (state)
  {
    case 0:
      engine.stop();
    break;
    case 1:
      engine.start();
    break;
  }
}


/**
 * @brief Functie om objecten te detecteren
 * 
 */
void detect_object()
{
  if (soon1.detectObstacle()) {
    engine.stop();
    delay(2000);
    steering.setZeroPoint();
    engine.start();
    engine.set_moving_state(2);

    unsigned short number = random(0, 300);

    if (number <= 149) {
      steering.turnLeft(27);
    } else if (number >= 150) {
      steering.turnRight(17);
    }

    engine.run_backward();
    delay(300);
    engine.stop();
    steering.setZeroPoint();
    engine.start();
    engine.set_moving_state(1);
    engine.run_forward();
  }
}