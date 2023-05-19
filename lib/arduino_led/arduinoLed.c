#include <util/delay.h>
#include <avr/io.h>

/* ################################ */
/*  Default LED On The Arduino Uno  */
/* ################################ */

void initLED() {
    // DDRB has 8 pins, but we want the 5th pin (5th pin is an output pin now)
    DDRB |= 0b00100000; 
}

void turnOnLED() {
    // pin is set high
    PORTB |= 0b00100000;
}

void turnOffLED() {
    // pin is set low (inverse(~) and & operator force pin 5 to be 0)
    PORTB &= ~0b00100000;
}
