#include "MKL25Z4.h"

#define PTB0_PIN 0
#define PTB1_PIN 1
#define PTC1_PIN 1  // TPM0_CH0
#define PTC2_PIN 2  // TPM0_CH1
#define PTC3_PIN 3  // TPM0_CH2
#define PTC4_PIN 4  // TPM0_CH3

//***** Music (From Prof) ********//
#define MUSICAL_NOTE_CNT sizeof(melody)  // 7
#define FREQ_2_MOD(x) (375000 / x)

//***** Motor ********//

#define INIT_PWM 0

#define PTB0_PIN 0
#define PTB1_PIN 1
#define MUSIC_PIN

#define PTC1_PIN 1       // TPM0_CH0
#define MOTOR_ONE_PIN 1  // TPM0_CH0

#define PTC2_PIN 2       // TPM0_CH1
#define MOTOR_TWO_PIN 2  // TPM0_CH1

#define PTC3_PIN 3         // TPM0_CH2
#define MOTOR_THREE_PIN 3  // TPM0_CH2

#define PTC4_PIN 4        // TPM0_CH3
#define MOTOR_FOUR_PIN 4  // TPM0_CH3

//***** Uart *****//

#define BAUD_RATE 9600
#define UART_TX_PORTE22 22
#define UART_RX_PORTE23 23
#define UART2_INT_PRIO 128

//***** RGB LED *******//

#define RED_LED 18
#define GREEN_LED 19
#define BLUE_LED 1

//****** Data Command *****//

// Command
#define VROOM_VROOM 0x00

// Data
#define INITIALISE 0x00
#define FORWARD_MOVE 0x01
#define FORWARD_LEFT_MOVE 0x02
#define FORWARD_RIGHT_MOVE 0x03
#define LEFT_MOVE 0x04
#define RIGHT_MOVE 0x05
#define BACK_MOVE 0x06
#define BACK_LEFT_MOVE 0x07
#define BACK_RIGHT_MOVE 0x08
#define STOP_MOVE 0x09

#define END_MOVE 0x0A

//****** Others ******//

#define MSG_COUNT 1

#define LED_RED 2  // 0b00000010
#define FUNCTION_MASK(x) (x & 0xF0)
#define LED_MASK(x) (x & 0x0F)
#define LED_FUNCTION 0x30

#define MASK(x) (1 << (x))

//
