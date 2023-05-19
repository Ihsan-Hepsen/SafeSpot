#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <usart.h>
#include <timer.h>
#include <ultrasonic.h>
#include <arduinoLed.h>
#include <orangeButton.h>
#include <led_matrix.h>
#include <gps.h>

#define MIN_RANGE 2 // 2cm
#define MAX_RANGE 400 // 400cm - 4m
#define IN_RANGE_MAX_LIMIT 375 // 70cm for now - IRL 400cm             
#define IN_RANGE_MIN_LIMIT 150 // 30cm for now - IRL 150cm
#define SIDE_ARROW_LIMIT 150 // 30cm for now - IRL 150cm

// |- - - - - - - - - - - - - - - - - - - - - -| o=o (bike)
// |------------------ 70cm -------------------| max range (any object within 70cm will be alerted) aka (danger zone)
// |--------- 40cm ---------|------------------- speed calculating interval
// -------------------------|------ 30cm ------| min limit (extreme denger zone)

// global variables
const int MULTIPLE = 250;
int timer_count;
int elapsed_time;
int interval_start = 0;
int interval_end = 0;
int inYellowZone = 0;
int inRedZone = 0;

int startProgram = 0;



void reportIncident() {
    // data transfer to Java FX application
    //printf("I");
    collectLocation();
    gpsSaved(1);
    _delay_ms(100);
    gpsSaved(0);

}

void detectObject() {
  light_up_led(63, 0, 0, 5);
}

void lightAlert() {
    backArrow(50,20,0);
}

void dangerAlert() {
    backArrow(160,0,0);
    _delay_ms(15);
    backArrow(20,0,0);
    _delay_ms(15);
}

void closeAlert() {
    backArrow(50,0,0);
}

void checkBlindSpot() {
  if (getDistance(2) < SIDE_ARROW_LIMIT) {
        sideArrow(50, 1);
      } else {
        sideArrow(0, 1);
      }

      if (getDistance(3) < SIDE_ARROW_LIMIT) {
        sideArrow(50, 0);
      } else {
        sideArrow(0, 0);
      }
}

// Interrupt for the timer, counting seconds
ISR(TIMER2_COMPA_vect) {
    timer_count++;
    if (timer_count % MULTIPLE == 0 && timer_count != 0) {
        ++elapsed_time;
    }
}

//ISR( PCINT0_vect )
//{
  // if ( bit_is_clear( PIND, PD1 ))
  // {
  //   _delay_us( 1000 );
  //   if ( bit_is_clear( PIND, PD1 )) {
    //  if (buttonPressed()) {
     //   light_up_led(62,6,9,2);
     // }
  //   }
  // }
//}


void setup() {
  //initUSART();
  initUltrasonic();
  enableTimer();
  enableButton();
  startTimer();
  init_led_matrix();
  turn_off_leds();
  init_gps();
  Serial.begin(9600); 
}

// void loop() {
//   if (getDistance(1) < 20) {
//     backArrow(10,0,0);
//   } else {
//     backArrow(0,0,0);
//   }
//   if (getDistance(2) < 20) {
//     sideArrow(10, 1);
//   } else {
//     sideArrow(0, 1);
//   }
//   if (getDistance(3) < 20) {
//     sideArrow(10, 0);
//   } else {
//     sideArrow(0, 0);
//   }
//   if (buttonReleased()) {
//     Serial.print("RELEASED\n");
//   } else {
//     Serial.print("PRESSED\n");
//     }
//   _delay_ms(500);

//   Serial.print(elapsed_time);
//   _delay_ms(1000);
// }

void loop() {
  if (!startProgram) {
    if (!buttonReleased()) {
      startProgram = 1;
      light_up_led(63,0,5,0);
      _delay_ms(1000);
      bootingAnimation(1);
    } else {
        startProgram = 0;
    }
  }
  if (startProgram) {
    int collectGPS = 0;
    elapsed_time = 0;
    // While something is detected and program is running
    while (startProgram) {
      // If the distance is futher then we care about reset all
      if (getDistance(1) > IN_RANGE_MAX_LIMIT) {
        backArrow(0,0,0);
        interval_start = 0;
        interval_end = 0;
        inRedZone = 0;
        inYellowZone = 0;
        // If distance is in danger zone
      } else if (getDistance(1) < IN_RANGE_MIN_LIMIT) {
        if (!inRedZone) {
          if (interval_start == 0) {
            interval_start = elapsed_time;
          }
          interval_end = elapsed_time; 
          inRedZone = 1;
          inYellowZone = 0;
        }
        
        if (interval_end - interval_start <= 2) {
          //reportIncident();
          // collect the gps location
          dangerAlert();
          collectGPS = 1;
          // if (getDistance(1) > IN_RANGE_MIN_LIMIT) {
          // interval_start = 0;
          // interval_end = 0;
          // }
        } else {
          closeAlert();
        }
        
      } else if (getDistance(1) > IN_RANGE_MIN_LIMIT) {
        if (!inYellowZone) {
          interval_start = elapsed_time; 
        }
        lightAlert();
        inYellowZone = 1;
        inRedZone = 0;
      }
      checkBlindSpot();
      //_delay_ms(8);
      // Turn off the system
      if (!buttonReleased()) {
        turn_off_leds();
        startProgram = 0;
        light_up_led(63,5,0,0);
        _delay_ms(1000);
        bootingAnimation(0);
      }
      if (collectGPS && !inRedZone && searchForGPSConnection()) {
          reportIncident();
          collectGPS = 0;
        }
    }
    if (startProgram) {
      checkBlindSpot();
    }
    if (!buttonReleased()) {
        turn_off_leds();
        startProgram = 0;
        light_up_led(63,5,0,0);
        _delay_ms(1000);
        bootingAnimation(0);
        turn_off_leds();
      }
  }
}

// void loop() {
//   init_gps();
//   init_led_matrix();

//   backArrow(10,10,10);
//   while (1)
//   {
//     collectLocation();
//      _delay_ms(200);
//   }
// }
  





