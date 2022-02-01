/**
 * @file communication.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 */


#ifndef COMMUNICATION
#define COMMUNICATION


#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>


#define     SSID                "H369A432F1F" // "Tesla IoT" //
#define     WIFI_PASSWORD       "3D6269C97CEA"// "fsL6HgjN" 
#define     WIFI_HOSTNAME       "supercar"
#define     SERVER_HOST         "192.168.2.8" // "145.24.238.50" // "192.168.2.8"
#define     SERVER_PORT         8080
#define     BUFFER_SIZE         8


void wifi_init();
String get_left();
String get_right();
String get_up();
String get_down();
String get_activate();
void send_data();
void stop_wifi();
void end_http();


#endif