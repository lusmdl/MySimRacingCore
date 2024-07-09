#ifdef __AVR_ATmega328P__

// HEADER
#include "MyAtmega328p.hpp"


/**
 * @brief Constructor of the MyAtmega328p class
 * Initializes the CPU frequency of the microcontroller.
 * 
 * @warning This method is considered unsafe in situations where incorrect CPU frequency can lead to system instability.
 * 
 * @note It is important to verify the compatibility of the specified frequency with the microcontroller specifications.
 * 
 * @example 
 * MyAtmega328p myController(F_CPU);
 */
MyAtmega328p ::MyAtmega328p(unsigned long f_cpu) {}




/**
 * @brief Tests the functionality of the microcontroller LED by turning it on and off for a specified duration.
 * 
 * @param delay The time to wait in milliseconds between turning the LED on and off
 * @warning This method may be unsafe in certain situations and unexpected behavior could occur.
 * @note Ensure the digital pin configuration and LED setup are correctly handled before calling this method.
 * @example 
 * MyAtmega328p myDevice;
 * myDevice.test(1000); // Turn the LED on and off with a delay of 1000ms
 */
void MyAtmega328p ::execTest(uint16_t delay) {

  // Den digitalen Pin als Ausgang konfigurieren
  // DDRB |= (1 << DDB5);
  setBit(DDRB, DDB5, true);

  // Die LED einschalten
  // PORTB |= (1 << PORTB5);
  setBit(PORTB, DDB5, true);
  execDelayMs(delay); // Eine Sekunde warten

  // Die LED ausschalten
  // PORTB &= ~(1 << PORTB5);
  setBit(PORTB, DDB5, false);
  execDelayMs(delay); // Eine Sekunde warten
}


/**
 * @brief Initializes UART communication on the MyAtmega328p.
 * Configures the baud rate, frame format settings, and outputs a "Hello World!" message via UART.
 * 
 * @param baudrate The desired baud rate for UART communication
 * 
 * @warning This method may encounter unforeseen issues and is considered unsafe in certain aspects.
 * 
 * @note It is important to configure the baud rate and frame format correctly to ensure proper communication.
 * 
 * @example 
 * MyAtmega328p myDevice;
 * myDevice.initUart(9600);
 */
void MyAtmega328p ::initUart(uint32_t baudrate) {

  uint16_t ubrr = F_CPU / (16 * baudrate) - 1;

  // Set baud rate

  UBRR0H = (uint8_t)(ubrr >> 8);
  UBRR0L = (uint8_t)ubrr;

  // Enable receiver and transmitter

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // Set frame format: 8data, 2stop bit

  // UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);

  printUart("\nHello World!\n");
}


/**
 * @brief Sends a character to the UART output buffer.
 * 
 * @param c The character to be sent
 * 
 * @warning This function blocks until the output buffer is ready to accept a character.
 * 
 * @note Make sure the UART hardware interface is properly configured before calling this function.
 * 
 * @example 
 * MyAtmega328p myAtmega;
 * myAtmega.putcharUart('A');
 */
void MyAtmega328p ::sendCharUart(char c) {

  while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}


/**
 * @brief Prints a string parameter over the UART.
 * 
 * @param str The string to be transmitted 
 * 
 * @warning This method may be unsafe in certain conditions.
 * 
 * @note Make sure the UART communication is properly configured before calling this method.
 * 
 * @example 
 * MyAtmega328p.atmega328p.printUart("Hello, world!");
 */
void MyAtmega328p ::printUart(const char *str) {

  const size_t len = strlen(str);
  for (size_t i = 0; i < len; i++) {

    sendCharUart(str[i]);
  }
}


/**
 * @brief Prints a string over the UART interface.
 * 
 * @param str The string to be printed
 * 
 * @warning This method may be unsafe in certain aspects and unexpected behavior can occur.
 * 
 * @note Make sure the UART communication is properly configured before calling this method.
 * 
 * @example 
 * MyAtmega328p atmegaDevice;
 * atmegaDevice.printUart("Hello, World!");
 */
void MyAtmega328p::printUart(const String &str) {

  const size_t len = str.length();
  for (size_t i = 0; i < len; i++) {

    sendCharUart(str.charAt(i));
  }
}


/**
 * @brief Configures Timer/Counter 0 (TC0) on the Atmega328p.
 * 
 * @param mode The desired mode for TC0 (e.g. ctc - Clear Timer on Compare Match)
 * @param prescaler The desired prescaler for TC0
 * @param value_top The desired comparison value for CTC mode
 * 
 * @warning Perform the calculation of time in the main code.
 * 
 * @note Refer to the table (in the MyAvr.cpp file) for setting Timer/Counter Mode of Operation and corresponding values.
 * 
 * @example
 * MyAtmega328p.setTC0Config(MyAtmega328p::tcModes::ctc, MyAtmega328p::tcPrescalers::prescalerValue, 100);
 */
void MyAtmega328p ::setTC0Config(enum_tcmodes mode, enum_tcprescalers prescaler, uint8_t value_top) {

  // Konfiguriere Timer/Counter 0
  // -
  // | Mode  | WGM02 | WGM01 | WGM00 | Timer/Counter Mode of Operation | TOP   | Update of OCR0x at TOV Flag Set on
  // | 0     | 0     | 0     | 0     | Normal                          | 0xFF  | Immediate MAX
  // | 1     | 0     | 0     | 1     | PWM, Phase Correct              | 0xFF  | TOP BOTTOM
  // | 2     | 0     | 1     | 0     | CTC                             | OCRA  | Immediate MAX
  // | 3     | 0     | 1     | 1     | Fast PWM                        | 0xFF  | BOTTOM MAX
  // | 5     | 1     | 0     | 1     | PWM, Phase Correct              | OCRA  | TOP BOTTOM
  // | 7     | 1     | 1     | 1     | Fast PWM                        | OCRA  | BOTTOM TOP
  
  switch (mode) {

    case CTC:

      // ctc modus einrichten

      setBit(TCCR0A, WGM00, 0);
      setBit(TCCR0A, WGM01, 1);
      setBit(TCCR0B, WGM02, 0);

      // prescaler
      auto n = setTC01Prescaler(prescaler, TCCR0B, CS02, CS01, CS00);


      // Setze den Vergleichswert für den CTC-Modus
      /*
      don't use this calculation. Do this in the main code instead!
      auto clkPerMillisekond { ( cpuFreq / n ) / 1000 };
      OCR0A = ( ( clkPerMillisekond * topTime ) - 1 );
      */

      OCR0A = value_top;

      // interrupt aktivieren

      setBit(TIMSK0, OCIE0A);
      sei();

      break;

    default:
      	
      break;
  }
}


/**
 * @brief Sets the prescaler for Timer/Counter0 to a specific value.
 * 
 * @param prescaler The desired prescaler value
 * @param reg The register where the bits for the prescaler will be set
 * @param bit_02 The position of Bit02 in the register
 * @param bit_01 The position of Bit01 in the register
 * @param bit_00 The position of Bit00 in the register
 * 
 * @return The set prescaler value (1, 8, 64, 256, 1024, or 0 for external clock source)
 * 
 * @warning This method may be unsafe in some situations where unexpected behavior could occur.
 * 
 * @note The prescaler values correspond to the clock frequency division ratios as shown in the Prescaler Table.
 * 
 * @example 
 * uint8_t prescalerReg = 0x00; // Initialize the register for prescaler settings
 * uint32_t prescalerValue = setTC01Prescaler(clk64, prescalerReg, 1, 2, 0);
 * // This sets the prescaler to 64 and updates the register accordingly
 */
uint32_t MyAtmega328p ::setTC01Prescaler(enum_tcprescalers prescaler, volatile uint8_t &reg, uint8_t bit_02, uint8_t bit_01, uint8_t bit_00) {

  // Prescaler Tabelle
  // -
  // |02 |01 |00 |
  // | 0 | 0 | 0 | No clock source (Timer/Counter stopped)
  // | 0 | 0 | 1 | clkI/O/1 (No prescaling)
  // | 0 | 1 | 0 | clkI/O/8 (From prescaler)
  // | 0 | 1 | 1 | clkI/O/64 (From prescaler)
  // | 1 | 0 | 0 | clkI/O/256 (From prescaler)
  // | 1 | 0 | 1 | clkI/O/1024 (From prescaler)
  // | 1 | 1 | 0 | External clock source on T0 pin. Clock on falling edge.
  // | 1 | 1 | 1 | External clock source on T0 pin. Clock on rising edge.
  
  switch (prescaler) {

    case CLK_1:

      setBit(reg, bit_00, true);
      setBit(reg, bit_01, false);
      setBit(reg, bit_02, false);
      return 1;
      break;

    case CLK_8:

      setBit(reg, bit_00, false);
      setBit(reg, bit_01, true);
      setBit(reg, bit_02, false);

      return 8;
      break;

    case CLK_64:

      setBit(reg, bit_00, true);
      setBit(reg, bit_01, true);
      setBit(reg, bit_02, false);

      return 64;
      break;

    case CLK_256:

      setBit(reg, bit_00, false);
      setBit(reg, bit_01, false);
      setBit(reg, bit_02, true);

      return 256;
      break;

    case CLK_1024:

      setBit(reg, bit_00, true);
      setBit(reg, bit_01, false);
      setBit(reg, bit_02, true);

      return 1024;
      break;

    case EXT_CLK_SOURCE_FALLING_EDGE:
      setBit(reg, bit_00, false);
      setBit(reg, bit_01, true);
      setBit(reg, bit_02, true);

      break;

    case EXT_CLK_SOURCE_RISING_EDGE:
      setBit(reg, bit_00, true);
      setBit(reg, bit_01, true);
      setBit(reg, bit_02, true);

      break;

    default:
      setBit(reg, bit_00, false);
      setBit(reg, bit_01, false);
      setBit(reg, bit_02, false);

      break;
  }

  return 0;
}


/**
 * @brief puts the ATmega328P microcontroller into the specified sleep mode.
 *        This method disables interrupts, sets the desired sleep mode, sets the power reduction bits,
 *        enables or disables BOD sleep mode based on the 'enable_bod_sleep' parameter, delays for three clock cycles,
 *        enables the sleep mode, enables interrupts, enters sleep mode, resumes execution after waking up,
 *        clears the power reduction bits, optionally enables BOD after sleep mode, and finally disables the sleep mode.
 * 
 * @param mode The sleep mode to enter.
 * @param bits_power_reduction The power reduction bits to set.
 * @param enable_bod_sleep Whether to enable BOD sleep mode or not.
 * 
 * 
 * @note Use Standby and Extended Standby sleep modes only with external crystals or resonators.
 * 
 * @warning This method assumes that the required functions 'setBit()', 'clearBit()', 'setBitMask()', 'clearBitMask()',
 *          'BITMASK()', 'PRR', and 'MCUCR' are properly defined.
 * 
 * @example 
 * MyAtmega328p avr;
 * avr.sleep(powerDown, 0x01, false);
 */
void MyAtmega328p::execSleep(enum_sleepmodes mode, uint8_t bits_power_reduction, bool enable_bod_sleep) {

  // Disable interrupts
  cli();

  // Disable sleep mode
  setBit(MCUCR, SE, false);

  // Set the requested sleep mode
  switch(mode) {

    case IDLE:

      clearBitMask(SMCR, BITMASK(SM0) | BITMASK(SM1) | BITMASK(SM2));

      break;

    case ADC_NOISE_REDUCTION:

      setBitMask(SMCR, BITMASK(SM0));
      clearBitMask(SMCR, BITMASK(SM1) | BITMASK(SM2));

      break;

    case POWER_DOWN:

      setBitMask(SMCR, BITMASK(SM1));
      clearBitMask(SMCR, BITMASK(SM2) | BITMASK(SM0)); 

      break;

    case POWER_SAVE:

      setBitMask(SMCR, BITMASK(SM0) | BITMASK(SM1));
      clearBitMask(SMCR, BITMASK(SM2));

      break;

    case STANDBY:

      // only recommend for use with external crystals or resonators

      clearBitMask(SMCR, BITMASK(SM0));
      setBitMask(SMCR, BITMASK(SM1) | BITMASK(SM2));

      break;

    case EXTENDED_STANDBY:

      // only recommend for use with external crystals or resonators

      setBitMask(SMCR, BITMASK(SM0) | BITMASK(SM1) | BITMASK(SM2) ); 

      break;

    default:

      // Invalid sleep mode, return imidiately

      return;
  }

  // Set the power reduction bits
  PRR |= bits_power_reduction;

  if (enable_bod_sleep) {

    // Enable BODS bit and set BODS to disable BOD in sleep mode if enableBODSleep is true

    setBit(MCUCR, BODS);
    setBit(MCUCR, BODSE);
    clearBit(MCUCR, BODSE);
  }

  // Delay for three clock cycles

  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  // Enable sleep mode
  setBit(SMCR, SE);

  // Enable interrupts
  sei();

  // Enter sleep mode
  asm volatile("sleep");

  // Execution will resume here after waking up
  //...

  // Clear the power reduction bits
  PRR &= ~bits_power_reduction;

  if (enable_bod_sleep) {

    // Re-enable BOD after sleep mode if enableBODSleep is true (optional)

    clearBit(MCUCR, BODS);
  }

  // Disable sleep mode

  setBit(MCUCR, SE, false);
  clearBitMask(SMCR, BITMASK(SM0) | BITMASK(SM1) | BITMASK(SM2));
}
#endif