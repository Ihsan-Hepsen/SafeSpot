#include <util/delay.h>
#include <avr/io.h>
#include <math.h>
#define NUMBER_OF_LEDS 4

void enableLed(int led) {
    if ( led < 0 || led > NUMBER_OF_LEDS-1 ) return;
      DDRB |= (1 << (PB2 + led)); 
                                               
}

void lightOn( int ledNumber ) {
    if ( ledNumber < 0 || ledNumber > NUMBER_OF_LEDS-1 ) return;
    PORTB &= ~( 1 << ( PB2 + ledNumber )); 
}

void lightOff ( int lednumber ) {
    if ( lednumber < 0 || lednumber > 3 ) return;
    PORTB |= ( 1 << ( PB2 + lednumber ));
}

void dimLED(int ledNumber, int percentage, int duration) {
  if (ledNumber < 0 || ledNumber > 3) {
    return;
  } 
  
  for (int i = 0; i < duration; i++) {
    lightOff(ledNumber);
    _delay_ms(percentage);
    lightOn(ledNumber);
    _delay_ms(100 / percentage);
    
  }
  lightOn(ledNumber); // turning the LED brightness fully back on
}

void enableAllLEDS() {
   for (int i = 0; i < NUMBER_OF_LEDS; i++)
  {
    enableLed(i);
    lightOff(i);
  }
}

void lightUpAllLEDS() {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    lightOn(i);
  }
}

void lightOffAllLEDS() {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    lightOff(i);
  }
}
