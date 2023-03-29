#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "MKL25Z4.h"                    // Device header
#include "constants.h"

#include "ledControl.h" 
#include "data_packet.h"
#include <stdbool.h>


volatile int running_green_LED_pos = 0;

int green_led_pos[4] = {MASK(LED_GREEN_PORTC8), MASK(LED_GREEN_PORTC9), MASK(LED_GREEN_PORTC10), MASK(LED_GREEN_PORTC11)};
int green_led_pos2[4] = {MASK(LED_GREEN_PORTB8), MASK(LED_GREEN_PORTB9), MASK(LED_GREEN_PORTB10), MASK(LED_GREEN_PORTB11)};

void onAllGreenLED (void) {
		PTB->PDOR |= (MASK(LED_GREEN_PORTB8) | MASK(LED_GREEN_PORTB9)| MASK(LED_GREEN_PORTB10)| MASK(LED_GREEN_PORTB11));
		PTC->PDOR |= MASK(LED_GREEN_PORTC8) | MASK(LED_GREEN_PORTC9)| MASK(LED_GREEN_PORTC10)| MASK(LED_GREEN_PORTC11);	
}

void offAllGreenLED (void) {
		PTB->PDOR &= ~(MASK(LED_GREEN_PORTB8) | MASK(LED_GREEN_PORTB9)| MASK(LED_GREEN_PORTB10)| MASK(LED_GREEN_PORTB11));
		PTC->PDOR &= ~(MASK(LED_GREEN_PORTC8) | MASK(LED_GREEN_PORTC9)| MASK(LED_GREEN_PORTC10)| MASK(LED_GREEN_PORTC11));	
}

void initRedLED(void) {
		// Enable Clock to PORTB and PORTC 
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
		
		// Configure MUX settings for GREEN LED
    PORTA->PCR[LED_RED_PORTA1] &= ~PORT_PCR_MUX_MASK; 
		PORTA->PCR[LED_RED_PORTA1] |= PORT_PCR_MUX(1); 	

		// Set Data Direction Registers for PortB and PortC    
		PTA->PDDR |= MASK(LED_RED_PORTA1);

		// Initialize to ON since car is stationary
		PTA->PDOR |= MASK(LED_RED_PORTA1);
}

void initGreenLED (void) {
		// Enable Clock to PORTB and PORTC 
		SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | (SIM_SCGC5_PORTC_MASK));
		
		// Configure MUX settings for GREEN LED
		for (int i = 8; i <= 11; i += 1) {
				PORTB->PCR[i] &= ~PORT_PCR_MUX_MASK; 
				PORTB->PCR[i] |= PORT_PCR_MUX(1); 
				PORTC->PCR[i] &= ~PORT_PCR_MUX_MASK; 
				PORTC->PCR[i] |= PORT_PCR_MUX(1); 			
		}

		// Set Data Direction Registers for PortB and PortC    
		PTB->PDDR |= (MASK(LED_GREEN_PORTB8) | MASK(LED_GREEN_PORTB9)| MASK(LED_GREEN_PORTB10)| MASK(LED_GREEN_PORTB11));
		PTC->PDDR |= (MASK(LED_GREEN_PORTC8) | MASK(LED_GREEN_PORTC9)| MASK(LED_GREEN_PORTC10)| MASK(LED_GREEN_PORTC11));

		// Initialize to ON since car is stationary
		onAllGreenLED();
}

void tMovingRedLED () {
//		for (;;) {
			PTA->PTOR |= MASK(LED_RED_PORTA1);
			osDelay(LED_TOGGLE_INTERVAL_1HZ);
		
//		}
}

void tStationaryRedLED () {
//		for (;;) {
			PTA->PTOR |= MASK(LED_RED_PORTA1);
			osDelay(LED_TOGGLE_INTERVAL_2HZ);
//		}
}

void tMovingGreenLED () {	
				for (int i = 0; i < 4; i += 1) {
					offAllGreenLED();	
					PTC->PDOR |= (green_led_pos[i]);
					
					osDelay(50);
				}
				
				for (int i = 0; i < 4; i += 1) {
					offAllGreenLED();
					PTB->PDOR |= (green_led_pos2[i]);
	
					osDelay(50);
				}
}

void tStationaryGreenLED () {
	onAllGreenLED();			
}	

