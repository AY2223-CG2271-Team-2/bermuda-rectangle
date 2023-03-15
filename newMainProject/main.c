/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "UART.h"


 
/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void app_main (void *argument) {
 
  // ...
  for (;;) {}
}
 
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  // ...
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  osThreadNew(app_main, NULL, NULL);    // Create application main thread
//  osKernelStart();                      // Start thread execution
//  for (;;) {}
	
	    //System initialization
	SystemCoreClockUpdate();
	InitGPIO();
	initUART2(BAUD_RATE);
	
	while(1) {
	
		if (led_control == 0x31) {
			Led_control_On(RED_LED);
		} else if (led_control == 0x30) {
			Led_control_Off(RED_LED);
		} else if (led_control == 0x33) {
			Led_control_On(GREEN_LED);
		} else if (led_control == 0x32) {
			Led_control_Off(GREEN_LED);
		} else if (led_control == 0x35) {
			Led_control_On(BLUE_LED);
		} else if (led_control == 0x34) {
			Led_control_Off(BLUE_LED);
		}
	}
}

