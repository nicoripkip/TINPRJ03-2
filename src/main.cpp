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
#define   IR_SENSOR_PIN_4       16
#define   IR_SENSOR_PIN_5       14
#define   IR_SENSOR_PIN_6       27

#define   ULTRASOON_PIN_1       35
#define   ULTRASOON_PIN_2       34

#define   ACCELEROMETER_PIN     0x11
#define   GYRO_PIN              0x12

#define   SERVO_PIN             0x17


void controller(); 
void check_running_state(int);
void automate_driving();
void turn_corners();
void detect_object();
void detect_ravine();


// Declareer objecten
DCEngine engine(MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2);           // Maakt een object aan voor de motor
IRSensor sensor1(IR_SENSOR_PIN_1);    // Kijkt voor een lijn voor de ACM
IRSensor sensor2(IR_SENSOR_PIN_2);    // Kijkt voor een lijn achter de ACM
IRSensor sensor3(IR_SENSOR_PIN_3);    // Kijkt voor een lijn aan de linkerkant voor van de ACM
IRSensor sensor4(IR_SENSOR_PIN_4);    // Kijkt voor een lijn aan de linkerkant achter van de ACM
IRSensor sensor5(IR_SENSOR_PIN_5);    // Kijkt voor een lijn aan de rechterkant voor van de ACM
IRSensor sensor6(IR_SENSOR_PIN_6);    // Kijkt voor een lijn aan de rechterkant achter van de ACM
Steering steering(SERVO_PIN);         // Object voor het 0------------------------------------------
UltraSoonSensor soon1(ULTRASOON_PIN_1, ULTRASOON_PIN_2);


int activate_state = 1;


/**
 * @brief Functie die alles opzet 
 * 
 */
void setup() 
{
  Serial.begin(9600);
  wifi_init();

  steering.setZeroPoint();
}


/**
 * @brief Functie die continue loopt
 * 
 */
void loop() 
{
  if (activate_state==1) {
    if (digitalRead(IR_SENSOR_PIN_1)==1) {
      detect_ravine();
    }
  }

  // controller();
  // check_running_state();

  sensor1.capture();
  sensor2.capture();
  sensor3.capture();
  sensor4.capture();
  sensor5.capture();
  sensor6.capture();

  soon1.detectObstacle();


  automate_driving();
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
 * @brief Functie voor het draaien van bochten
 * 
 */
void turn_corners()
{
  engine.stop();
  delay(2000);
  if (sensor3.getActive() == HIGH) {
    steering.turnRight(17);
    engine.start();
    engine.set_moving_state(2);
    engine.run_backward();
    delay(1000);
    steering.setZeroPoint();
    engine.set_moving_state(1);
    engine.run_forward();
  } else if (sensor4.getActive() == HIGH) {
    steering.turnLeft(27);
    engine.start();
    engine.set_moving_state(1);
    engine.run_forward();
    delay(1000);
    engine.stop();
  } else if (sensor5.getActive() == HIGH) {
    steering.turnLeft(27);
    engine.start();
    engine.set_moving_state(2);
    engine.run_backward();
    delay(1000);
    engine.stop();
  } else if (sensor6.getActive() == HIGH) {
    steering.turnRight(17);
    engine.start();
    engine.set_moving_state(1);
    engine.run_forward();
    delay(1000);
    engine.stop();
  }

  steering.setZeroPoint();
  engine.start();
  engine.set_moving_state(1);
  engine.run_forward();
}


/**
 * @brief Functie voor het autonoom rijden
 * 
 */
void automate_driving()
{
  check_running_state(activate_state);

  if (activate_state == 1) {
    engine.set_moving_state(1);
    engine.run_forward();

    detect_object();

    if (sensor1.crossedLine() && sensor3.crossedLine() || sensor1.crossedLine() && sensor5.crossedLine() || sensor1.crossedLine()) {
      detect_ravine();
    } 

    if (sensor3.crossedLine() || sensor4.crossedLine() || sensor5.crossedLine() || sensor6.crossedLine()) {
      turn_corners();
    }
  } else {
    Serial.println("[error]\tHij wil niet starten!");
  }
}


/**
 * @brief Functie voo rhet detecteren van een afgrond
 * 
 */
void detect_ravine()
{ 
  engine.stop();
  delay(2000);
  engine.start();

  if (sensor2.crossedLine()) {
    engine.set_moving_state(2);
    engine.run_backward();
    delay(500);
    engine.stop();
  }

  if (sensor3.crossedLine() || sensor6.crossedLine()) {             // Als links vrij is
    steering.turnLeft(27);
  } else if (sensor5.crossedLine() || sensor4.crossedLine()) {      // Als rechts vrij is
    steering.turnRight(17);
  } else {                                                          // Als er geen zijkanten vrij is
    int rand = random(0, 100);
    if (rand >= 50) {
      steering.turnLeft(27);
    } else if (rand <= 49) {
      steering.turnRight(17);
    }
  }

  engine.start();
  engine.set_moving_state(2);
  engine.run_backward();
  for (int i = 0; i < 8000000;i++) {
    if (sensor4.crossedLine() || sensor6.crossedLine()) {
      turn_corners();
    }


    if (digitalRead(IR_SENSOR_PIN_2)) {
      engine.stop();
      delay(500);

      steering.setZeroPoint();
      engine.set_moving_state(1);
      engine.run_forward();
      delay(1000);
      break;
    } 
  }
  engine.stop();  

  delay(500);

  engine.start();
  engine.set_moving_state(1);
  engine.run_forward();
  delay(1000);
  steering.setZeroPoint();
}


/**
 * @brief Functie voor het detecteren en handelen bij obstakels
 * 
 */
void detect_object()
{

}