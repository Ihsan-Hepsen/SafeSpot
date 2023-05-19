#include <Adafruit_NeoPixel.h>
 
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            5
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
void init_led_matrix() 
{
  pixels.begin(); // This initializes the NeoPixel library.
}

void turn_off_leds() {
  for(int i=0;i<64;i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0));
      pixels.show(); 
    }
}

void light_up_led(int led, int r, int g, int b) {
  pixels.setPixelColor(led, pixels.Color(r,g,b));
  pixels.show();
}

void backArrow(int r, int g, int b) {
  int backArrow[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 24, 25, 32, 33, 40, 41, 48, 49, 56, 57};
  for(int i=0;i<28;i++)
  {
    pixels.setPixelColor(backArrow[i], pixels.Color(r,g,b));
    pixels.show(); 
  }
}

void sideArrow(int brightness, int left) {
  int leftArrow[] = {19, 20, 21, 22, 23, 28, 29, 30, 31, 38, 39, 46, 47, 55};
  int rightArrow[] = {26, 34, 35, 42, 43, 50, 51, 52, 53, 58, 59, 60, 61, 62};
  if (left) {
    for(int i=0;i<14;i++)
    {
      pixels.setPixelColor(leftArrow[i], pixels.Color(brightness,brightness/6,0));
      pixels.show(); 
    }
  } else {
    for(int i=0;i<14;i++)
    {
      pixels.setPixelColor(rightArrow[i], pixels.Color(brightness,brightness/6,0));
      pixels.show(); 
    }
  }
}

void gpsSaved(int on) {
  int gpsSaved[] = {36, 37, 44, 45};
  if (on) {
  
    for(int i=0;i<4;i++)
    {
      pixels.setPixelColor(gpsSaved[i], pixels.Color(0,0,40));
      pixels.show(); 
    }
  } else
 {
   for(int i=0;i<4;i++)
    {
      pixels.setPixelColor(gpsSaved[i], pixels.Color(0,0,0));
      pixels.show(); 
    }
 }  
}

void bootingAnimation(int up) {
  int red = 40;
  int green = 0;

  if(up) {
    red = 0;
    green = 40;
  }

  int line[] = {63, 54, 45, 36, 27, 18, 9, 0};

  for (int i = 0; i < 8; i++)
  {
    pixels.setPixelColor(line[i], pixels.Color(red,green,0));
    pixels.show();
    _delay_ms(70);
  }
  turn_off_leds();
}

void fullDisplay(int r, int g, int b) {
  for(int i=0;i<64;i++)
    {
      pixels.setPixelColor(i, pixels.Color(r,g,b));
      pixels.show(); 
    }
}