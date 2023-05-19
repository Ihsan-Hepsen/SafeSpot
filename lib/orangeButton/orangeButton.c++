#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <orangeButton.h>

#define OUTPUT DDRD
#define INPUT DDRC

void enableButton() {
    OUTPUT = OUTPUT | (1 << 4);
    INPUT = INPUT & ~(1 << 5);
}

int buttonReleased() {
    if ((PINC & (1 << PC4)) == 0) {
        return 1;
    }
    return 0;
}

int buttonPressed() {
    if ((PIND & (1 << PD5)) == 1) {
        return 1;
    }
    return 0;
}