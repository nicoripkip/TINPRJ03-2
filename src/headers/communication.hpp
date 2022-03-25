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


#define     SSID                "Tesla IoT" // "H369A432F1F" 
#define     WIFI_PASSWORD       "fsL6HgjN" // "3D6269C97CEA"
// #define     SSID                "H369A432F1F" 
// #define     WIFI_PASSWORD       "3D6269C97CEA"
#define     WIFI_HOSTNAME       "supercar"
#define     BUFFER_SIZE         8

const String SERVER_HOST = "145.24.238.4"; // "192.168.2.8" 
const int SERVER_PORT = 8080;


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