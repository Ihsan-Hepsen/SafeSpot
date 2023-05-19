#include <util/delay.h>
#include <avr/io.h>
#include <math.h>

void enableLed(int ledNnumber);

void lightOn(int ledNumber);

void lightOff(int ledNumber);

void enableAllLEDS();

void lightUpAllLEDS();

void lightOffAllLEDS();

void dimLED(int ledNumber, int percentage, int duration);
