#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "ultrasonic.h"
#include <util/delay.h>
// temp
#include <Arduino.h>

static volatile uint32_t first_reading = 0;
static volatile uint32_t second_reading = 0;
static volatile uint32_t duty_cycle = 0;

// Center Ultrasonic
# define echoPinC 8 // Echo Pin 
# define trigPinC 6 // Trigger Pin 

// Left Ultrasonic
# define echoPinL 13 // Echo Pin 
# define trigPinL 11 // Trigger Pin 

// Right Ultrasonic
# define echoPinR 12 // Echo Pin 
# define trigPinR 10 // Trigger Pin 

int LedPin=13;
int maxRange = 400; // Maximum range  
int minRange = 0; // Minimum range  
void initUltrasonic() 
{ 
    pinMode(trigPinC, OUTPUT); 
    pinMode(echoPinC, INPUT); 

	pinMode(trigPinL, OUTPUT); 
    pinMode(echoPinL, INPUT); 

	pinMode(trigPinR, OUTPUT); 
    pinMode(echoPinR, INPUT); 
} 

uint32_t getDistance(int ultrasonic){
	int trigPin;
	int echoPin;
	if (ultrasonic == 1) {
		trigPin = trigPinC;
		echoPin = echoPinC;
	} else if (ultrasonic == 2) {
		trigPin = trigPinL;
		echoPin = echoPinL;
	} else if (ultrasonic == 3) {
		trigPin = trigPinR;
		echoPin = echoPinR;
	}
	
	int answer = 0;
	static uint32_t cm;
	while (!answer)
	{
		long dur, dist; // Duration used to calculate distance 
		digitalWrite(trigPin, LOW); 
    	delayMicroseconds(20); 
    	digitalWrite(trigPin, HIGH); 
    	delayMicroseconds(20); 
    	digitalWrite(trigPin, LOW); 
    	dur = pulseIn(echoPin, HIGH); 
    	dist = dur / 58.2; 
		cm = dist;

		if (cm > 2) {
			answer = 1;
		}
	}
	_delay_ms(6);
	return cm;
}

ISR(TIMER1_CAPT_vect) {
	if ((TCCR1B & (1 << ICES1)) == (1 << ICES1)) {
		first_reading = ICR1;
	}
	else {
		second_reading = ICR1;
	}
	
	if (first_reading != 0 && second_reading != 0){
		duty_cycle = second_reading - first_reading;
		first_reading = 0;
		second_reading = 0;
	}
	
	TCCR1B ^= ( 1<< ICES1); //toggle edge detection bit
	TIFR1 = (1 << ICF1); //clear Input Capture Flag
}


