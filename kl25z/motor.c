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
  delay(0x1000);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  delay(0x1000);
}

void moveleft(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;
  delay(0x1000);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  delay(0x1000);
}

void moveforwardright(int _pwm) {
  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;
  delay(0x1000);
  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  delay(0x1000);
}

void moveforwardleft(int _pwm) {
  TPM0_C1V = 0x0EA6;
  TPM0_C0V = 0;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;
  delay(0x1000);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0x0EA6;
  TPM0_C2V = 0;
  delay(0x1000);
}

void movebackwardright(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0;
  TPM0_C2V = 0x0EA6;
  delay(0x1000);
  TPM0_C1V = 0;
  TPM0_C0V = 0;
  TPM0_C3V = 0;
  TPM0_C2V = 0x0EA6;
  delay(0x1000);
}

void movebackwardleft(int _pwm) {
  TPM0_C1V = 0;
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0;
  TPM0_C2V = 0x0EA6;
  delay(0x1000);
  TPM0_C1V = 0;
  TPM0_C0V = 0x0EA6;
  TPM0_C3V = 0;
  TPM0_C2V = 0;
  delay(0x1000);
}
