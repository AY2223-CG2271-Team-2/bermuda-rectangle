#include "RTE_Components.h"
#include CMSIS_device_header
#include "UART.h"
#include "cmsis_os2.h"
#include "constants.h"
#include "data_packet.h"
#include "init.h"
#include "music.h"

#define SPEED 0xFFFF
#define TURN_SPEED 0x0030

void moveforward(int _pwm) {
  TPM0_C1V = SPEED;
  TPM0_C0V = 0;
  TPM0_C3V = SPEED;
  TPM0_C2V = 0;
}

void movestop(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
}

void movebackward(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = SPEED;
  TPM0_C3V = 0;
  TPM0_C2V = SPEED;
}

void moveright(int _pwm) {
  TPM0_C1V = TURN_SPEED;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = TURN_SPEED;
}

void moveleft(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = TURN_SPEED;
  TPM0_C3V = TURN_SPEED;
  TPM0_C2V = 0;
}

void moveforwardright(int _pwm) {
  TPM0_C1V = SPEED;
  TPM0_C0V = 0;
  TPM0_C3V = SPEED;
  TPM0_C2V = 0;
  osDelay(50);
  TPM0_C1V = SPEED;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  osDelay(25);
}

void moveforwardleft(int _pwm) {
  TPM0_C1V = SPEED;
  TPM0_C0V = 0;
  TPM0_C3V = SPEED;
  TPM0_C2V = 0;
  osDelay(25);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = SPEED;
  TPM0_C2V = 0;
  osDelay(25);
}

void movebackwardright(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = SPEED;
  TPM0_C3V = 0;
  TPM0_C2V = SPEED;
  osDelay(25);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = SPEED;
  osDelay(25);
}

void movebackwardleft(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = SPEED;
  TPM0_C3V = 0;
  TPM0_C2V = SPEED;
  osDelay(25);
  TPM0_C1V = 0;
  TPM0_C0V = SPEED;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  osDelay(25);
}
