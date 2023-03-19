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
#include "ledControl.h"
#include "motor.h"
#include "music.h"

osSemaphoreId_t audioSemaphore;
osMessageQueueId_t controlQ, audioQ, motorQ, backLedRedQ, frontLedGreenQ;
data_packet_t global_packet;

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void app_main(void *argument) {
  // ...
  for (;;) {
  }
}

void tMotor(void *argument) {
  data_packet_t _packet;

  osStatus_t _debug;

  for (;;) {
    _debug = osMessageQueueGet(motorQ, &_packet, NULL, osWaitForever);
    if (_packet.data == RIGHT_MOVE) {
      moveright();
    } else if (_packet.data == LEFT_MOVE) {
      moveleft();
    } else if (_packet.data == FORWARD_MOVE) {
      Led_control_On(RED_LED);
      moveforward();
    } else if (_packet.data == STOP_MOVE) {
      Led_control_Off(RED_LED);
      movestop();
    } else if (_packet.data == BACK_MOVE) {
      movebackward();
    } else if (_packet.data == FORWARD_RIGHT_MOVE) {
      Led_control_On(RED_LED);
      moveforwardright();
    } else if (_packet.data == FORWARD_LEFT_MOVE) {
      Led_control_On(RED_LED);
      moveforwardleft();
    } else if (_packet.data == BACK_LEFT_MOVE) {
      Led_control_On(RED_LED);
      movebackwardleft();
    } else if (_packet.data == BACK_RIGHT_MOVE) {
      Led_control_On(RED_LED);
      movebackwardright();
    }
  }
}

void tAudio(void *argument) {
  // ...
  data_packet_t _packet;

  for (;;) {
    osMessageQueueGet(audioQ, &_packet, NULL, 0);
    if (_packet.data != END_MOVE) {
      astronomia();
    } else {
      // FIXME: Switch of audio issue
      osSemaphoreAcquire(audioSemaphore, osWaitForever);
      playEndingMusic();
    }
  }
}

void tControl(void *argument) {
  for (;;) {
    osMessageQueueGet(controlQ, &global_packet, NULL, osWaitForever);
    osMessageQueuePut(motorQ, &global_packet, NULL, 0);
    osMessageQueuePut(audioQ, &global_packet, NULL, 0);
  }
}

int main(void) {
  // System Initialization
  SystemCoreClockUpdate();
  InitGPIO();
  initUART2(BAUD_RATE);
  initPWM();
  initRedLED();
  initGreenLED();

  // Init Queue
  controlQ = osMessageQueueNew(MSG_COUNT, sizeof(data_packet_t), NULL);
  audioQ = osMessageQueueNew(MSG_COUNT, sizeof(data_packet_t), NULL);
  motorQ = osMessageQueueNew(MSG_COUNT, sizeof(data_packet_t), NULL);
  backLedRedQ = osMessageQueueNew(MSG_COUNT, sizeof(data_packet_t), NULL);
  frontLedGreenQ = osMessageQueueNew(MSG_COUNT, sizeof(data_packet_t), NULL);

  osKernelInitialize();  // Initialize CMSIS-RTOS
  audioSemaphore = osThreadNew(tControl, NULL, NULL);
  osThreadNew(tMotor, NULL, NULL);
  osThreadNew(tAudio, NULL, NULL);
  osKernelStart();  // Start thread execution
  for (;;) {
  }
}
