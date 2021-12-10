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


#define PWM_CHANNEL 0 // Kanaal waarop het signaal zit
#define PWM_RESOLUTION 8 // Dit is het aantal bits voor de register van het pwm gebeuren
#define PWM_FREQUENTIE 5000 // Frequentie is 5KHZ


/**
 * @brief Klasse opgezet voor het runnen van de DC engine
 * 
 */
class DCEngine
{
    private:
        bool _onOff;
        bool _backForward;
        double _speed;
        double _multiplier;

    public:
        DCEngine(int);
        void init_spi_ports(int esc_pin_1, int esc_pin_2, int esc_pin_3);
        void run_forward(int esc_pin_2);
        void run_backward(int esc_pin_1, int esc_pin_2, int esc_pin_3);
        void start();
        void stop();
        double temperature();
        void setSpeed(double);
        double getSpeed();
        void setAcceleration(double);
        double getAcceleration();
        void accelerate();
        void message(char c[5]);
};

#endif