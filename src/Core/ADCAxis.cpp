#include "ADCAxis.hpp"

#ifdef __AVR_ATmega32U4__
/**
 * @brief Constructor for ADCAxis class
 * 
 * @param pin The analog pin number the axis is connected to
 */
ADCAxis::ADCAxis(uint8_t pin) : 
    pin_(pin),
    rawMin_(0), 
    rawMax_(1023),
    rawAct_(0)
{
    // Constructor initializes pin, act, min, and max values

    data_.act = 0;
    data_.min = 0;
    data_.max = 100;

    // Configure the ADC
    ADMUX = (1 << REFS0); // AVcc with external capacitor at AREF pin
    ADCSRA = (1 << ADEN)  // Enable ADC
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler of 128
}

void ADCAxis::begin() {


}

void ADCAxis::updateRawData() {

    rawAct_ = readADC();

    #ifdef LUSMDL_DEBUGMODE
    Serial.print("actual raw ADC value from ");
    Serial.print(reinterpret_cast<uintptr_t>(this), HEX); 
    Serial.print(":\t\t\t" + String(rawAct_) + "\n");
    _delay_ms(100);
    #endif
}

int ADCAxis::readADC() {
    // Select the analog pin (0-7)
    ADMUX = (ADMUX & 0xF0) | (pin_ & 0x0F);

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));

    // Read the ADC value
    return ADC;
}

#endif // __AVR_ATmega32U4__


/**
 * @brief Sets the minimum value for the axis based on current raw value
 * 
 * @param min The minimum value to be set
 */
int ADCAxis::setMin(float min) {

    rawMin_ = rawAct_;
    data_.min = min;

    return rawMin_;
}

void ADCAxis::setMin(float min, int raw) {

    rawMin_ = raw;
    data_.min = min;
}

/**
 * @brief Sets the maximum value for the axis based on current raw value
 * 
 * @param max The maximum value to be set
 */
int ADCAxis::setMax(float max) {
    rawMax_ = rawAct_;
    data_.max = max;

    return rawMax_;
}

void ADCAxis::setMax(float min, int raw) {

    rawMax_ = raw;
    data_.max = min;
}



/**
 * @brief Gets the current data of the axis, including the scaled actual value
 *
 * @return pod_axis The current data of the axis
 */
pod_axis ADCAxis::getData() {

    // Calculate the range of the raw values
    //int rawRange = rawMax_ - rawMin_;
    
    // Calculate the difference between the current raw value and the minimum raw value
    //int rawValueOffset = rawAct_ - rawMin_;
    
    // Calculate the range of the scaled values
    //float scaledRange = data_.max - data_.min;
    
    // Calculate the proportion of the raw value within its range
    //float valueProportion = static_cast<float>(rawAct_ - rawMin_) / static_cast<float>(rawMax_ - rawMin_);
    
    // Calculate the scaled actual value
    //data_.act = data_.min + valueProportion * scaledRange;
    data_.act = data_.min + (static_cast<float>(rawAct_ - rawMin_) / static_cast<float>(rawMax_ - rawMin_)) * (data_.max - data_.min);

    return data_;
}
