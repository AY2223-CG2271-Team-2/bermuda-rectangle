
#include "MKL25Z4.h"

void initPWM(void); 
void InitGPIO(void);
void initUART2(uint32_t baud_rate);

static void delay(volatile uint32_t nof);
void delay_mult40(volatile uint32_t nof);