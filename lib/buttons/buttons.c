#include <util/delay.h>
#include <avr/io.h>

#define MAX_NUMBER_OF_BUTTONS 3

void enableButton(int buttonNumber) {
  if (buttonNumber < 1 || buttonNumber > MAX_NUMBER_OF_BUTTONS) {
    return;

  } else if (buttonNumber == 1) {
    DDRC &= ~(1 << PC1);
    PORTC |= (1 << PC1);
  } else if (buttonNumber == 2) {
    DDRC &= ~(1 << PC2);
    PORTC |= (1 << PC2);
  } else if (buttonNumber == 3) {
    DDRC &= ~(1 << PC3);
    PORTC |= (1 << PC3);
  }

}

int buttonPressed(int button) {
  if (button < 0 || button > MAX_NUMBER_OF_BUTTONS) {
    return -1;
  } else if ((((PINC & (1 << PC1)) == 0)) && button == 1) {
    return 1;
  } else if ((((PINC & (1 << PC2)) == 0)) && button == 2) {
    return 1;
  } else if ((((PINC & (1 << PC3)) == 0)) && button == 3) {
    return 1;
  } else {
    return 0;
  }
}


int buttonReleased(int button) {
  if (button < 0 || button > MAX_NUMBER_OF_BUTTONS) {
    return -1;
  } else if (!((PINC & (1 << PC1)) == 1) && button == 1) {
    return 1;
  } else if (!((PINC & (1 << PC2)) == 1) && button == 2) {
    return 1;
  } else if (!((PINC & (1 << PC3)) == 1) && button == 3) {
    return 1;
  } else {
    return 0;
  }
}

void enableAllButtons() {
  for (int i = 0; i < MAX_NUMBER_OF_BUTTONS; i++)
  {
    enableButton(i);
  }
}
