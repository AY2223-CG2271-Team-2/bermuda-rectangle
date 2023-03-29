
#include "constants.h"
#include "init.h"

//Delay function 
static void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}

void delay_mult40(volatile uint32_t nof) {
  for(int i=0;i<40;i++) {
    delay(nof);
  }
}


/* initiPWM() */
void initPWM(void) 
{
  //Enable Clock Getting for PORTB
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	//Enable Clock Getting for PORTC
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
  
  //Configure Mode 3 for the PWM pin operation
  PORTB ->PCR[PTB0_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTB -> PCR[PTB0_PIN] |= PORT_PCR_MUX(3);
  
  PORTB ->PCR[PTB1_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTB -> PCR[PTB1_PIN] |= PORT_PCR_MUX(3);
	
	PORTC ->PCR[PTC1_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTC -> PCR[PTC1_PIN] |= PORT_PCR_MUX(4);
	
	PORTC ->PCR[PTC2_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTC -> PCR[PTC2_PIN] |= PORT_PCR_MUX(4);
	
	PORTC ->PCR[PTC3_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTC -> PCR[PTC3_PIN] |= PORT_PCR_MUX(4);
	
	PORTC ->PCR[PTC4_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTC -> PCR[PTC4_PIN] |= PORT_PCR_MUX(4);
  
  //Enable Clock Gating for Timer1
  SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
  //Enable Clock Gating for Timer0
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
  
  //Select clock for TPM module
  SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
  SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); //MCGFLLCLK or MCGPLCLK
  
  //Set Modulo Value 20971520 /128 = 163840 /3276 = 50
  //TPM1->MOD = 3276
  
  //Set Modulo Value 48000000/128 = 375000 /7500 = 50
  TPM1->MOD = 7500;
	
	//Set Modulo Value 48000000/128 = 375000 /7500 = 50
  TPM0->MOD = 75;
  
  /*Edge-Aligned PWM*/
  //Update SnC register:CMOD = 01, PS=111 (128)
  TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
  TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
  TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
  TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
  TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
  /**/
  
  //Enable PWM on TPM1 Channel 0 -> PTB0 
  TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
  TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
  
  //Enable PWM on TPM1 Channel 1 -> PTB1
  TPM1_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
  TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	 //Enable PWM on TPM0 Channel 0 -> PTC1
  TPM0_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
  TPM0_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
  
  //Enable PWM on TPM0 Channel 1 -> PTC2
  TPM0_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
  TPM0_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	//Enable PWM on TPM0 Channel 2 -> PTC3
  TPM0_C2SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
  TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
  
  //Enable PWM on TPM0 Channel 3 -> PTC4
  TPM0_C3SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
  TPM0_C3SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	// Speaker
  TPM1_C0V = 3750;
	
}

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