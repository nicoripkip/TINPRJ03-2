/** ===========================================================================================
 * @file ultrasoonsensor.hpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022 - 01 - 14
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#ifndef ULTRA_SOON_SENSOR
#define ULTRA_SOON_SENSOR


#include <Arduino.h>
#include "headers/sensors.hpp"


class UltraSoonSensor : public Sensor
{
    private:
        int _pin1;
        int _pin2;
        float _distance;

    public:
        UltraSoonSensor(int, int);
        float getDistance();
        void setDistance(float);
        bool detectObstacle();
};


#endif