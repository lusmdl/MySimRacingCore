#ifndef MYWS2812B_HPP
#define MYWS2812B_HPP

#include "MyNeoPixels.hpp"

class MyWS2812B : public MyNeoPixels {


    private:

        // MEMBER

        // Registers

        // Data pin Data Direction Register 
        volatile uint8_t *ptrDataDirectionRegister_; 

        // Data pin PORT register
        volatile uint8_t *ptrPortRegister_;

        // here comes the information for the poiter
        uint8_t *ptrPortRegisterMemAddr_;

        // Data pin Number (register bit)
        uint8_t pin_;

        // LED data

        enum_colormapping colorMapping_;
        pod_rgb *colorMapped_;

        pod_rgb *color_;
        //uint8_t maxNumberOfLeds_;
        //uint8_t* brightness_;
        pod_leddata data_;

        // SETTER

        void inline setLedsPin(pod_rgb *led_array, uint16_t leds, uint8_t pin_mask);
        void sendArray(uint8_t *data, uint16_t data_len);
        void inline sendArrayMask(uint8_t *data, uint16_t data_len, uint8_t maskhi);
        void inline setLeds (pod_rgb  *led_array, uint16_t number_of_leds);
        double calculateBrightness (uint8_t bright, uint8_t led);


    protected:


    public:

        // CONSTRUCTOR

        MyWS2812B(volatile uint8_t &ddrx, volatile uint8_t &portx, uint8_t *sfr_mem_addr_portx, uint8_t pin_number, uint8_t max_number_of_leds = 255, enum_colormapping color_mapping = GRB);


        // DESTRUCTOR

        ~MyWS2812B();


        // SETTER

        // FOR ONE SPECIFIC LED

        void setColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
        void setColor(uint8_t led, enum_colormodes mode);
        void setColor(uint8_t led, pod_rgb &color);
        void setBrightness(uint8_t n, uint8_t led);
        void clearColor(uint8_t led);

        // FOR ALL LEDS

        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void setColor(enum_colormodes mode);
        void setColor(pod_rgb &color);
        void setBrightness(uint8_t n);
        void clearColor();
        
        // EXECUTE

        void show();

        // GETTER

        pod_rgb getColor(uint8_t led);
        pod_leddata getLedsData();
};
#endif // MYWS2812B_HPP