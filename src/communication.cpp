/** ===========================================================================================
 * @file communication.cpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022 - 01 - 29
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#include "./headers/communication.hpp"
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


HTTPClient http;


/**
 * @brief Functie voor het opzetten van de internet verbinding
 * 
 */
void wifi_init() 
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, WIFI_PASSWORD);
    WiFi.setHostname(WIFI_HOSTNAME);

    Serial.print("[info]\tVerbind met wifi: ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println(WiFi.localIP());
}


/**
 * @brief 
 * 
 */
void send_data()
{

}


/**
 * @brief Get the data object
 * 
 */
String get_data()
{
    Serial.println("[info]\tHaal data op van de api!");
    String uri = "http://192.168.2.8:8080/api/get";
    http.begin(uri);
    http.GET();

    return http.getString();
}


/**
 * @brief Functie voor het sluiten van http
 * 
 */
void end_http()
{
    http.end();
}


/**
 * @brief Functie voor het stoppen van het internet
 * 
 */
void stop_wifi()
{
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.disconnect();
    }
}