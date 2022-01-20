/** ===========================================================================================
 * @file sensors.hpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#ifndef SENSORS
#define SENSORS


/**
 * @brief Klasse voor de sensor
 * 
 */
class Sensor {
    private:
        int _active;
        int _pin;
        void setPinMode();

    public:
        Sensor();
        void setActive(int);
        int getActive();
        void setPin(int);
        int getPin();
        void capture();
};

#endif