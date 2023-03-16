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
  

  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;

  delay_mult100(10000);

  TPM0_C0V = 0;
  TPM0_C1V = 0;
  TPM0_C2V = 0;
  TPM0_C3V = 0;

  // Speaker
  TPM1_C0V = 3750;

  while (1) {
    playStarWars();

    //		if (led_control == 0x31) {
    //			Led_control_On(RED_LED);
    //		} else if (led_control == 0x30) {
    //			Led_control_Off(RED_LED);
    //		} else if (led_control == 0x33) {
    //			Led_control_On(GREEN_LED);
    //		} else if (led_control == 0x32) {
    //			Led_control_Off(GREEN_LED);
    //		} else if (led_control == 0x35) {
    //			Led_control_On(BLUE_LED);
    //		} else if (led_control == 0x34) {
    //			Led_control_Off(BLUE_LED);
    //		}

    // TODO: change led_contorl function name

    if (led_control == FORWARD_MOVE) {
      Led_control_On(RED_LED);
      TPM0_C1V = 0x0EA6;
      TPM0_C0V = 0;
      TPM0_C3V = 0x0EA6;
      TPM0_C2V = 0;
    } else if (led_control == STOP_MOVE) {
			Led_control_Off(RED_LED);
			TPM0_C1V = 0;
      TPM0_C0V = 0;
      TPM0_C3V = 0;
      TPM0_C2V = 0;
    } else if (led_control == 0x33) {
    } else if (led_control == 0x32) {
    } else if (led_control == 0x35) {
    } else if (led_control == 0x34) {
    }
  }

}
