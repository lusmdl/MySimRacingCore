#ifdef __AVR_ATmega328P__

#ifndef ATMEGA328PISR_H
#define ATMEGA328PISR_H

#include <avr/interrupt.h>


extern "C" {

    // External Interrupt Request 0
    ISR(INT0_vect);
    
    // External Interrupt Request 1
    ISR(INT1_vect);
    
    // Pin Change Interrupt Request 0
    ISR(PCINT0_vect);
    
    // Pin Change Interrupt Request 1
    ISR(PCINT1_vect);
    
    // Pin Change Interrupt Request 2
    ISR(PCINT2_vect);
    
    // Watchdog Time-out Interrupt
    ISR(WDT_vect);
    
    // Timer/Counter2 Compare Match A
    ISR(TIMER2_COMPA_vect);
    
    // Timer/Counter2 Compare Match B
    ISR(TIMER2_COMPB_vect);
    
    // Timer/Counter2 Overflow
    ISR(TIMER2_OVF_vect);
    
    // Timer/Counter1 Capture Event
    ISR(TIMER1_CAPT_vect);
    
    // Timer/Counter1 Compare Match A
    ISR(TIMER1_COMPA_vect);
    
    // Timer/Counter1 Compare Match B
    ISR(TIMER1_COMPB_vect);
    
    // Timer/Counter1 Overflow
    ISR(TIMER1_OVF_vect);
    
    // Timer/Counter0 Compare Match A 
    ISR(TIMER0_COMPA_vect);
    
    // Timer/Counter0 Compare Match B
    ISR(TIMER0_COMPB_vect);
    
    // Timer/Counter0 Overflow
    ISR(TIMER0_OVF_vect);
    
    // SPI Serial Transfer Complete
    ISR(SPI_STC_vect);
    
    // USART Rx Complete
    ISR(USART_RX_vect);
    
    // USART, Data Register Empty
    ISR(USART_UDRE_vect);
    
    // USART Tx Complete
    ISR(USART_TX_vect);
    
    // ADC Conversion Complete
    ISR(ADC_vect);
    
    // EEPROM Ready
    ISR(EE_READY_vect);
    
    // Analog Comparator
    ISR(ANALOG_COMP_vect);
    
    // 2-wire Serial Interface
    ISR(TWI_vect);
    
    // Store Program Memory Ready
    ISR(SPM_READY_vect);
}
#endif
#endif