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


#define   REED_PIN              0x01

#define   MOTOR1_PIN1           32
#define   MOTOR1_PIN2           19
#define   MOTOR2_PIN1           2
#define   MOTOR2_PIN2           4

#define   IR_SENSOR_PIN_1       22
#define   IR_SENSOR_PIN_2       21
#define   IR_SENSOR_PIN_3       17
#define   IR_SENSOR_PIN_4       27

#define   ULTRASOON_PIN_1       35
#define   ULTRASOON_PIN_2       34

#define   SERVO_PIN             0x17


void controller(); 
void check_running_state(int);
void detect_line();


// Declareer objecten
DCEngine engine(MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2);           // Maakt een object aan voor de motor
IRSensor sensor1(IR_SENSOR_PIN_1);    // Kijkt voor een lijn voor de ACM
IRSensor sensor2(IR_SENSOR_PIN_2);    // Kijkt voor een lijn achter de ACM
IRSensor sensor3(IR_SENSOR_PIN_3);    // Kijkt voor een lijn aan de linkerkant voor van de ACM
IRSensor sensor4(IR_SENSOR_PIN_4);    // Kijkt voor een lijn aan de linkerkant achter van de ACM
Steering steering(SERVO_PIN);         // Object voor het 0------------------------------------------
UltraSoonSensor soon1(ULTRASOON_PIN_1, ULTRASOON_PIN_2);


int activate_state = 1;
volatile bool engine_state = true;
volatile bool front_detected = false;
volatile bool back_detected = false;
volatile bool left_detected = false;
volatile bool right_detected = false;


/**
 * @brief Functie die alles opzet 
 * 
 */
void setup() 
{
  Serial.begin(9600);
  // wifi_init();
  
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN_1), detect_line, FALLING);
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN_2), detect_line, FALLING);
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN_3), detect_line, FALLING);
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN_4), detect_line, FALLING);

  steering.setZeroPoint();
  delay(1000);
}


/**
 * @brief Functie die continue loopt
 * 
 */
void loop() 
{
  engine.set_moving_state(1);

  if (engine_state == false && front_detected == true && back_detected == false) {
    steering.setZeroPoint();
    engine.start();
    engine.set_moving_state(2);

    if (left_detected == true && right_detected == false) {
      // steering.turnLeft(27);
    } else if (right_detected == true && left_detected == false) {
      // steering.turnRight(17);
    } else {
      steering.setZeroPoint();
    }

    engine.run_backward();
    interrupts();

    engine_state = true;
    front_detected = false;
    back_detected = false;

    delay(500);
    engine.set_moving_state(1);
    engine.run_forward();
  } else if (engine_state == false && back_detected == true && front_detected == false) {
    steering.setZeroPoint();
    engine.start();
    engine.set_moving_state(1);

    if (left_detected == true && right_detected == false) {
      steering.turnLeft(27);
    } else if (right_detected == true && left_detected == false) {
      steering.turnRight(17);
    } else {
      steering.setZeroPoint();
    }

    engine.run_forward();
    interrupts();

    engine_state = true;
    front_detected = false;
    back_detected = false;

    delay(500);
    engine.set_moving_state(2);
    engine.run_backward();
  }

  switch (engine_state) {
    case true:
      engine.start();
    break;
    case false:
      engine.stop();
    break;
  }

  Serial.print("Motor status loop: ");
  Serial.println(engine_state);
}


/**
 * @brief 
 * 
 */
void detect_line()
{
   noInterrupts();

  // Rechtsboven
  if (!sensor1.crossedLine()) {
    engine_state = false;
    front_detected = true;
    back_detected = false;
    right_detected = true;
  } else if (!sensor2.crossedLine()) {
    engine_state = false;
    front_detected = true;
    back_detected = false;
    left_detected = true;
  } else if (!sensor3.crossedLine()) {
    engine_state = false;
    back_detected = true;
    front_detected = false;
  } else if (!sensor4.crossedLine()) {
    engine_state = false;
    back_detected = true;
    front_detected = false;
  }
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
