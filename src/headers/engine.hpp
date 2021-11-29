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


/**
 * @brief Klasse opgezet voor het runnen van de DC engine
 * 
 */
class DCEngine
{
    private:
        bool _onOff;
        int speed;

    public:
        void init_spi_ports(int esc_pin_1, int esc_pin_2, int esc_pin_3);
        void run_forward(int esc_pin_1, int esc_pin_2, int esc_pin_3);
        void run_backward(int esc_pin_1, int esc_pin_2, int esc_pin_3);
        void start();
        void stop();
        double temperature();
        double speedy();
        void message(char c[5]);
};

#endif