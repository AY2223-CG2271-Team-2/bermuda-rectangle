#include "MKL25Z4.h"

// PORT PIN CONFIGURATIONS FOR LED
#define LED_RED_PORTA1     1
#define LED_GREEN_PORTB8   8
#define LED_GREEN_PORTB9   9
#define LED_GREEN_PORTB10 10
#define LED_GREEN_PORTB11 11
#define LED_GREEN_PORTC8   8
#define LED_GREEN_PORTC9   9
#define LED_GREEN_PORTC10 10
#define LED_GREEN_PORTC11 11

// MOD & CnV value for Red LED
#define LED_RED_MOVING_MOD_VALUE      375000
#define LED_RED_MOVING_CnV_VALUE      LED_RED_MOVING_MOD_VALUE / 2          // 50% Duty Cycle

#define LED_RED_STATIONARY_MOD_VALUE	187500
#define LED_RED_STATIONARY_CnV_VALUE  LED_RED_STATIONARY_MOD_VALUE / 2      // 50% Duty Cycle

//Delay timing for the LED
#define LED_TOGGLE_INTERVAL_1HZ 500
#define LED_TOGGLE_INTERVAL_2HZ 250

#define isMoving 1  // bool variable to check if car is moving (To be removed)

void initRedLED();
void initGreenLED();
void tMovingGreenLED();
void tStationaryGreenLED();
void tStationaryRedLED();