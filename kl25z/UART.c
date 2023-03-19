#include "UART.h"

#include "MKL25Z4.h"
#include "constants.h"
#include "data_packet.h"

// volatile uint8_t rx_data = 0;
extern osMessageQueueId_t controlQ;
extern osSemaphoreId_t audioSemaphore;

/* Delay routine */
void delay(volatile uint32_t nof) {
  while (nof != 0) {
    __asm("NOP");
    nof--;
  }
}

void Led_control_On(enum color_t color) {
  if (color == BLUE_LED) {
    PTD->PDOR &= ~MASK(color);  // Turns led on
  } else {
    PTB->PDOR &= ~MASK(color);  // Turns led on
  }
}

void Led_control_Off(enum color_t color) {
  if (color == BLUE_LED) {
    PTD->PDOR |= MASK(color);  // Turns led off
  } else {
    PTB->PDOR |= MASK(color);  // Turns led off
  }
}

void UART2_IRQHandler() {
  NVIC_ClearPendingIRQ(UART2_IRQn);
  data_packet_t packet;

  // Receiver Interrupt Handler
  if (UART2->S1 & UART_S1_RDRF_MASK) {
    UART2->C2 &= ~UART_C2_TIE_MASK;
    packet.data = UART2->D;
    osMessageQueuePut(controlQ, &packet, NULL, 0);

    if (packet.data == END_MOVE) {
      osSemaphoreRelease(audioSemaphore);
    }
  }

  PORTE->ISFR |= MASK(UART_RX_PORTE23);
}
