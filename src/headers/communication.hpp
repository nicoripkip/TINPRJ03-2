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


#define     SSID                "Tesla IoT" //"H369A432F1F"
#define     WIFI_PASSWORD       "fsL6HgjN" //"3D6269C97CEA"
#define     WIFI_HOSTNAME       "supercar"
#define     SERVER_HOST         "145.24.238.50" // "192.168.2.8"
#define     SERVER_PORT         8080
#define     BUFFER_SIZE         8


void wifi_init();
String get_data();
void send_data();
void stop_wifi();
void end_http();


#endif