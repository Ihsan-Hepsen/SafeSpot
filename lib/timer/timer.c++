#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void enableTimer() {
    TCCR2A |=  _BV(WGM21);  
    TIMSK2 |= _BV(OCIE1A);
    OCR2A = 249;
    sei();
}

void startTimer() {
    TCCR2B |= _BV(CS22) | _BV(CS21); 
}

void stopTimer() {
    TCCR2B &= ~_BV(CS22) & ~_BV(CS21);
}
