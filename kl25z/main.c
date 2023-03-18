/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include CMSIS_device_header
#include "UART.h"
#include "cmsis_os2.h"
#include "constants.h"
#include "data_packet.h"
#include "init.h"
#include "music.h"
#include "motor.h"

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void app_main(void *argument) {
  // ...
  for (;;) {
  }
}

int main(void) {
  // System Initialization
  SystemCoreClockUpdate();
	InitGPIO();
  initUART2(BAUD_RATE);
  initPWM();
  // ...

  osKernelInitialize();               // Initialize CMSIS-RTOS
  osThreadNew(app_main, NULL, NULL);  // Create application main thread
                                      //  osKernelStart();                      // Start thread execution
                                      //  for (;;) {}

  // System initialization
  

  // Speaker
  TPM1_C0V = 3750;

  while (1) {
		

    // TODO: change led_contorl function name
    if (led_control == FORWARD_MOVE) {
      Led_control_On(RED_LED);
      moveforward();
    } else if (led_control == STOP_MOVE) {
			Led_control_Off(RED_LED);
			movestop();
    } else if (led_control == BACK_MOVE) {
			movebackward();
    } else if (led_control == RIGHT_MOVE) {
			moveright();
    } else if (led_control == LEFT_MOVE) {
			moveleft();
    } else if (led_control == FORWARD_RIGHT_MOVE) {
			Led_control_On(RED_LED);
      moveforwardright();
    } else if (led_control == FORWARD_LEFT_MOVE) {
			Led_control_On(RED_LED);
      moveforwardleft();
    } else if (led_control == BACK_LEFT_MOVE) {
			Led_control_On(RED_LED);
      movebackwardleft();
		} else if (led_control == BACK_RIGHT_MOVE) {
			Led_control_On(RED_LED);
      movebackwardright();
		}
		
  }

}
