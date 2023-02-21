#include "MKL25Z4.h"
#include "audio.h"

#define PTB0_Pin 0
#define PTB1_Pin 1 
#define MUSICAL_NOTE_CNT sizeof(melody)
#define FREQ_2_MOD(x) (375000 / x)



int musical_notes[] = {NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6};


/* initiPWM() */
void initPWM(void) 
{
	//Enable Clock Getting for PORTB
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	//Configure Mode 3 for the PWM pin operation
	PORTB ->PCR[PTB0_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB -> PCR[PTB0_Pin] |= PORT_PCR_MUX(3);
	
	PORTB ->PCR[PTB1_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB -> PCR[PTB1_Pin] |= PORT_PCR_MUX(3);
	
	//Enable Clock Gating for Timer1
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	//Select clock for TPM module
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); //MCGFLLCLK or MCGPLCLK
	
	//Set Modulo Value 20971520 /128 = 163840 /3276 = 50
	//TPM1->MOD = 3276
	
	//Set Modulo Value 48000000/128 = 375000 /7500 = 50
	TPM1->MOD = 7500;
	
	/*Edge-Aligned PWM*/
	//Update SnC register:CMOD = 01, PS=111 (128)
	TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	/**/
	
	//Enable PWM on TPM1 Channel 0 -> PTB0 
	TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	//Enable PWM on TPM1 Channel 1 -> PTB1
	TPM1_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
}

//Delay function 
static void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}

void delay_mult100(volatile uint32_t nof) {
	for(int i=0;i<100;i++) {
		delay(nof);
	}
}
int main(void) {                                                	
	char i = 0;
	SystemCoreClockUpdate();
	initPWM();
	//TPM1_C0V = 0;
	
	//TPM1_C0V = 0x0666;  //1638 (half of 3276) -50%
	TPM1_C0V = 3750;    // 0xEA6 = 3750 (half Of 7500) -> 50%
	//TPM1_C1V = 0x0EA6;
	

	while(1) {
		for (i = 0; i < MUSICAL_NOTE_CNT; i += 1) {
				TPM1->MOD = FREQ_2_MOD(melody[i]);
				TPM1_C0V = FREQ_2_MOD(melody[i])/2;
//			
				delay_mult100(0x9FF);
			}
		}
}