#include "MKL25Z4.h"                    // Device header
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#define UART_HEADER

#define BAUD_RATE 9600
#define UART_TX_PORTE22 22 
#define UART_RX_PORTE23 23
#define UART2_INT_PRIO 128

extern volatile uint8_t led_control;

extern enum color_t {
	RED_LED = 18,   //PortB Pin 18 
	GREEN_LED = 19, //PortB Pin 19
	BLUE_LED = 1    //PortD pin 1
} color_t;

void InitGPIO(void);
void Led_control_On(enum color_t color);
void Led_control_Off(enum color_t color);
void initUART2(uint32_t);

void UART2_IRQHandler(void);
