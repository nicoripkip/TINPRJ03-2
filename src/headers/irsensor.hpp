/** ===========================================================================================
 * @file irsensor.hpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#ifndef IR_SENSOR
#define IR_SENSOR

#include "headers/sensors.hpp"


class IRSensor : Sensor
{
    private:
        double _distance;

    public:
        IRSensor(int);
        void setDistance(double);
        double getDistance();
        bool crossedLine();
};


#endif