/** ===========================================================================================
 * @file engine.hpp
 * @author Nico van Ommen (nikovanommen.nvo@gmail.com)
 * @brief 
 * @version 1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * ===========================================================================================*/


#ifndef ENGINE
#define ENGINE


#define RUN_FORWARD 1
#define RUN_BACKWARD 2


/**
 * @brief Klasse opgezet voor het runnen van de DC engine
 * 
 */
class DCEngine
{
    private:
        int _motor1_pin1;
        int _motor1_pin2;
        int _motor2_pin1;
        int _motor2_pin2;
        bool _life_state;
        int _moving_state;

    public:
        DCEngine(int, int, int, int);
        void start();
        void stop();
        void run_forward();
        void run_backward();
        void print();
        void set_motor1_pin1(int);
        int get_motor1_pin1();
        void set_motor1_pin2(int);
        int get_motor1_pin2();
        void set_motor2_pin1(int);
        int get_motor2_pin1();
        void set_motor2_pin2(int);
        int get_motor2_pin2();
        void set_life_state(bool);
        bool get_life_state();
        void set_moving_state(int);
        int get_moving_state();
};

#endif