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


class Steering 
{
    private:
        int _pin;
        int _speed;
        int _turn_degree;

    public:
        Steering(int);
        void setSpeed(int);
        int getSpeed();
        void setTurnDegree(int);
        int getTurnDegree();
        void turnLeft();
        void turnRight();
};


#endif 