#include "RTE_Components.h"
#include CMSIS_device_header
#include "UART.h"
#include "cmsis_os2.h"
#include "constants.h"
#include "data_packet.h"
#include "init.h"
#include "music.h"

void moveforward(int _pwm) {
  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0x0EA6;
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
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0;
  TPM0_C2V = 0x0EA6;
}

void moveright(int _pwm) {
  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0x0EA6;
  osDelay(50);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  osDelay(50);
}

void moveleft(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;
  osDelay(50);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  osDelay(50);
}

void moveforwardright(int _pwm) {
  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;
  osDelay(50);
  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  osDelay(50);
}

void moveforwardleft(int _pwm) {
  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;
  osDelay(50);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;
  osDelay(50);
}

void movebackwardright(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0;
  TPM0_C2V = 0x0EA6;
  osDelay(50);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0x0EA6;
  osDelay(50);
}

void movebackwardleft(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0;
  TPM0_C2V = 0x0EA6;
  osDelay(50);
  TPM0_C1V = 0;
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  osDelay(50);
}
