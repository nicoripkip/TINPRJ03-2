/**
 * @file steering.hpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 */


#ifndef STEERING
#define STEERING


#define     PWM_CHANNEL         2           // Kanaal waarop het signaal zit
#define     PWM_RESOLUTION      8        // Dit is het aantal bits voor de register van het pwm gebeuren
#define     PWM_FREQUENTIE      50       // Frequentie is 5KHZ

#define     LEFT                1
#define     RIGHT               2
#define     MIDDLE              3


class Steering 
{
    private:
        int _pin;
        int _speed;
        int _turn_degree;
        int _servo_state;
        void setState(int);

    public:
        Steering(int);
        void setSpeed(int);
        int getSpeed();
        void setTurnDegree(int);
        int getTurnDegree();
        void turnLeft(int);
        void turnRight(int);
        void setZeroPoint();
        int getState();
};


#endif 