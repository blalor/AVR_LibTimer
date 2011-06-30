/*
    LED: PB4
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "8bit_tiny_timer0.h"

const Timer0Registers timer0Regs = {
    &GTCCR,
    &TCCR0A,
    &TCCR0B,
    &OCR0A,
    &TIMSK,
    &TIFR,
    &TCNT0
};

void flash_led() {
    PORTB ^= _BV(PB4);
}

int main(int argc, char **argv) {
    DDRB |= _BV(PB4);
    PORTB &= ~_BV(PB4);
    
    timer0_init(&timer0Regs, TIMER0_PRESCALE_1024);  // 128 µS/tick
    timer0_set_ocra_interrupt_handler(flash_led);
    timer0_enable_ocra_interrupt();
    
    timer0_start();
    
    sei();
    
    for (;;) {}
    
    return 0; // never reached
}
