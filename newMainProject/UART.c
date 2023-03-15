#include "MKL25Z4.h"
#include "UART.h"

#define LED_RED 2 //0b00000010
#define FUNCTION_MASK(x) (x & 0xF0)
#define LED_MASK(x) (x & 0x0F)
#define LED_FUNCTION 0x30

#define MASK(x) (1 << (x))

volatile uint8_t led_control = 0;

//Initiate the necessary LEDs
void InitGPIO(void) 
{ 
 // Enable Clock to PORTB and PORTD 
 SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | (SIM_SCGC5_PORTD_MASK)); 
  
 // Configure MUX settings to make all 3 pins GPIO 
 PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK; 
 PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1); 
  
 PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK; 
 PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1); 
  
 PORTD->PCR[BLUE_LED] &= ~PORT_PCR_MUX_MASK; 
 PORTD->PCR[BLUE_LED] |= PORT_PCR_MUX(1); 
  
 // Set Data Direction Registers for PortB and PortD 
 PTB->PDDR |= (MASK(RED_LED) | MASK(GREEN_LED)); 
 PTD->PDDR |= MASK(BLUE_LED);    
	
 //Set all LED to OFF (PDOR Writing Output Port Data which write value of 1 to bit x) As this is a logic low circuit, logic high would turn the LED off.)
 PTB->PDOR |= (MASK(RED_LED) | MASK(GREEN_LED));
 PTD->PDOR |= (MASK(BLUE_LED));
} 

/*Init UART2 */
void initUART2(uint32_t baud_rate) {
	uint32_t divisor, bus_clock;

	//Enable clock for Port E and UART2 
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	
	//Connect UART pins for PTE22 PTE23
	PORTE->PCR[UART_TX_PORTE22] &= ~PORT_PCR_MUX_MASK; //Clear the bits of the current mux operation
	PORTE->PCR[UART_TX_PORTE22] |= PORT_PCR_MUX(4); //Turn on
	
	PORTE->PCR[UART_RX_PORTE23] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[UART_RX_PORTE23] |= PORT_PCR_MUX(4);
	
	//Ensure Tx and Rx are disabled before configuration
	UART2->C2 &= ~((UART_C2_TE_MASK) | (UART_C2_RE_MASK));
	
	//Set Baud Rate to desired value
	bus_clock = (DEFAULT_SYSTEM_CLOCK)/2;
	divisor = bus_clock/(baud_rate * 16);
	UART2->BDH = UART_BDH_SBR(divisor >> 8);
	UART2->BDL = UART_BDL_SBR(divisor);
	
	//No Parity, 8-bits
	UART2->C1 = 0;
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	//Enable transmitter and receiver
	UART2->C2 |= UART_C2_RE_MASK;
	
	NVIC_SetPriority(UART2_IRQn,128);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	//Enable the Interrupt
	NVIC_EnableIRQ(UART2_IRQn);
	
	//Enable TIE for (Tx Interrupt) and RIE (Rx Interrupt)
	UART2->C2 |= UART0_C2_RIE_MASK;
	
}

/* Delay routine */
void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}

void Led_control_On(enum color_t color) {
	if(color == BLUE_LED) {
		PTD->PDOR &= ~MASK(color);  //Turns led on
	} else {
		PTB->PDOR &= ~MASK(color);  //Turns led on
	}
}

void Led_control_Off(enum color_t color) {
	if(color == BLUE_LED) {
		PTD->PDOR |= MASK(color); //Turns led off
	} else {
		PTB->PDOR |= MASK(color); //Turns led off
	}
}

void UART2_IRQHandler() {
	NVIC_ClearPendingIRQ(UART2_IRQn);
	
	//Receiver Interrupt Handler
	if(UART2->S1 & UART_S1_RDRF_MASK) {
		UART2-> C2 &= ~UART_C2_TIE_MASK;
		led_control = UART2->D;		
	}
}
