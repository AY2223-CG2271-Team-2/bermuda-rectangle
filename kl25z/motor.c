#include "RTE_Components.h"
#include CMSIS_device_header
#include "UART.h"
#include "cmsis_os2.h"
#include "constants.h"
#include "data_packet.h"
#include "init.h"
#include "music.h"


void moveforward() {
	TPM0_C1V = 0x0EA6;
	TPM0_C0V = 0;
	TPM0_C3V = 0x0EA6;
	TPM0_C2V = 0;
}

void movestop() {
	TPM0_C1V = 0;
	TPM0_C0V = 0;
	TPM0_C3V = 0;
	TPM0_C2V = 0;
}

void movebackward() {
	TPM0_C1V = 0;
	TPM0_C0V = 0x0EA6;
	TPM0_C3V = 0;
	TPM0_C2V = 0x0EA6;
}

void moveright() {
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

void moveleft() {
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

void moveforwardright() {
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

void moveforwardleft() {
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

void movebackwardright() {
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

void movebackwardleft() {
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