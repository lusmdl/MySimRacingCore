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

    #ifdef LSMDL_DEBUGMODE
    Serial.print("actual raw ADC value from ");
    Serial.print(reinterpret_cast<uintptr_t>(this), HEX); 
    Serial.print(". The value is: " + String(rawAct_) + "\n");
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
void ADCAxis::setMinHere(double min) {

    rawMin_ = rawAct_;
    data_.min = min;
}


/**
 * @brief Sets the maximum value for the axis based on current raw value
 * 
 * @param max The maximum value to be set
 */
void ADCAxis::setMaxHere(double max) {
    rawMax_ = rawAct_;
    data_.max = max;
}



/**
 * @brief Gets the current data of the axis, including the scaled actual value
 *
 * @return pod_axis The current data of the axis
 */
pod_axis ADCAxis::getData() {

    // Calculate the range of the raw values
    auto rawRange = rawMax_ - rawMin_;
    
    // Calculate the difference between the current raw value and the minimum raw value
    auto rawValueOffset = rawAct_ - rawMin_;
    
    // Calculate the range of the scaled values
    auto scaledRange = data_.max - data_.min;
    
    // Calculate the proportion of the raw value within its range
    auto valueProportion = static_cast<double>(rawValueOffset) / rawRange;
    
    // Calculate the scaled actual value
    data_.act = data_.min + valueProportion * scaledRange;

    // Example calculation with rawValue = -1256:
    // rawMin_ = 100, rawMax_ = 300, data_.min = -50, data_.max = 50
    // rawRange = 300 - 100 = 200
    // rawValueOffset = -1256 - 100 = -1356
    // scaledRange = 50 - (-50) = 100
    // valueProportion = -1356 / 200 = -6.78
    // data_.act = -50 + (-6.78 * 100) = -50 - 678 = -728

    

    #ifdef LSMDL_DEBUGMODE
    Serial.print("actual data values from ");
    Serial.print(reinterpret_cast<uintptr_t>(this), HEX); 
    Serial.print(". The data structur:\tmin\tact\tmax\t\n\t\t\t\t\t\t");
    Serial.print(String(data_.min) + "\t" + String(data_.act) + "\t" + String(data_.max) + "\n"); 
    _delay_ms(100);
    #endif

    return data_;
}
