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
#include "motor.h"
#include "music.h"

// osMessageQueueId_t audioQ, motorQ, backLedRedQ, frontLedGreenQ;

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void app_main(void *argument) {
  // ...
  for (;;) {
  }
}

void motor_control_thread(void *argument) {
  data_packet_t _data;

  _data.cmd = VROOM_VROOM;
  _data.data = STOP_MOVE;

  for (;;) {
  }
}

void audio_thread(void *argument) {
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

  // osKernelInitialize();  // Initialize CMSIS-RTOS
  // osThreadNew(motor_control_thread, NULL, NULL);
  // osThreadNew(app_main, NULL, NULL);  // Create application main thread
  // osKernelStart();  // Start thread execution
  //  for (;;) {}

  // Speaker
  TPM1_C0V = 3750;

  while (1) {
    if (rx_data == RIGHT_MOVE) {
      moveright();
    } else if (rx_data == LEFT_MOVE) {
      moveleft();
    } else if (rx_data == FORWARD_MOVE) {
      Led_control_On(RED_LED);
      moveforward();
    } else if (rx_data == STOP_MOVE) {
      Led_control_Off(RED_LED);
      movestop();
    } else if (rx_data == BACK_MOVE) {
      movebackward();
    } else if (rx_data == FORWARD_RIGHT_MOVE) {
      Led_control_On(RED_LED);
      moveforwardright();
    } else if (rx_data == FORWARD_LEFT_MOVE) {
      Led_control_On(RED_LED);
      moveforwardleft();
    } else if (rx_data == BACK_LEFT_MOVE) {
      Led_control_On(RED_LED);
      movebackwardleft();
    } else if (rx_data == BACK_RIGHT_MOVE) {
      Led_control_On(RED_LED);
      movebackwardright();
    }
  }
}
