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


#define PWM_CHANNEL 1           // Kanaal waarop het signaal zit
#define PWM_RESOLUTION 8        // Dit is het aantal bits voor de register van het pwm gebeuren
#define PWM_FREQUENTIE 490      // Frequentie is 5KHZ
#define ESC_ARM_VALUE 176       // Dit is de waarde om de ESC te armen
#define ESC_MAX_ARM_SEQUENCE 12 // Dit is de maximale aantal aan ARM signals verzonden naar de ESC


/**
 * @brief Klasse opgezet voor het runnen van de DC engine
 * 
 */
class DCEngine
{
    private:
        bool _onOff;
        bool _backForward;
        int _speed;
        double _multiplier;

    public:
        DCEngine(int);
        void init_spi_ports(int esc_pin_1, int esc_pin_2, int esc_pin_3);
        void run_forward();
        void run_backward();
        void arm();
        void start();
        void stop();
        double temperature();
        void setSpeed(int);
        int getSpeed();
        void setAcceleration(double);
        double getAcceleration();
        void accelerate();
        void message(char c[5]);
        void print();
};

#endif