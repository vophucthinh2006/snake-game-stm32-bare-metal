#include "FOUR_BIT_LED.h"

static volatile uint32_t *LED_BSRR;
static volatile uint32_t *LED_BRR;

static uint8_t LATCH_PIN;
static uint8_t CLOCK_PIN;
static uint8_t DATA_PIN;

static const uint8_t SEG_CODE[17] =
{
	0b11000000, //0
	0b11111001, //1
	0b10100100, //2
	0b10110000, //3
	0b10011001, //4
	0b10010010, //5
	0b10000010, //6
	0b11111000, //7
	0b10000000, //8
	0b10010000, //9
	0b10001100, //A
	0b10111111, //B
	0b11000110, //C
	0b10100001, //D
	0b10000110, //E
	0b11111111, //F
    0xBF        // -
};

/*
		BIT_0
	BIT_5	BIT_1
		BIT6
	BIT_4	BIT_2
		BIT_3		BIT_7
*/

void FOUR_BIT_LED_Config(
		GPIO_PORT_t port,
        uint8_t latch_pin,
        uint8_t clock_pin,
        uint8_t data_pin
		){
    switch(port){
        case GPIO_PORTA:
            LED_BSRR = &GPIOA_BSRR;
            LED_BRR  = &GPIOA_BRR;
            break;

        case GPIO_PORTB:
            LED_BSRR = &GPIOB_BSRR;
            LED_BRR  = &GPIOB_BRR;
            break;

        case GPIO_PORTC:
            LED_BSRR = &GPIOC_BSRR;
            LED_BRR  = &GPIOC_BRR;
            break;

        default:
            return;
    }

    LATCH_PIN = latch_pin;
    CLOCK_PIN = clock_pin;
    DATA_PIN  = data_pin;
}

void FOUR_BIT_LED_Send16(uint16_t data){
    *LED_BRR = (1 << LATCH_PIN);

    for(int i = 15; i >= 0; i--)
    {
        if(data & (1 << i)) *LED_BSRR = (1 << DATA_PIN);
        else                *LED_BRR  = (1 << DATA_PIN);

        //for(volatile int i = 0; i < 1; i++);
        *LED_BRR  = (1 << CLOCK_PIN);
        //or(volatile int i = 0; i < 1; i++);
        *LED_BSRR = (1 << CLOCK_PIN);
    }
    //for(volatile int i = 0; i < 1; i++);
    *LED_BSRR = (1 << LATCH_PIN);
}

void FOUR_BIT_LED_Display(
		uint8_t digit1,
		uint8_t digit2,
		uint8_t digit3,
		uint8_t digit4
		){
    uint16_t data;

    data = ((uint16_t)SEG_CODE[digit1] << 8) | 0x08;
    FOUR_BIT_LED_Send16(data);

    data = ((uint16_t)SEG_CODE[digit2] << 8) | 0x04;
    FOUR_BIT_LED_Send16(data);

    data = ((uint16_t)SEG_CODE[digit3] << 8) | 0x02;
    FOUR_BIT_LED_Send16(data);

    data = ((uint16_t)SEG_CODE[digit4] << 8) | 0x01;
    FOUR_BIT_LED_Send16(data);
}

void FOUR_BIT_LED_Scan(
		uint8_t digit1,
		uint8_t digit2,
		uint8_t digit3,
		uint8_t digit4
		){
	static uint8_t digit = 1;

	switch(digit){
	case 1: FOUR_BIT_LED_Send16(((uint16_t)SEG_CODE[digit1] << 8 | 0x08)); break;
	case 2: FOUR_BIT_LED_Send16(((uint16_t)SEG_CODE[digit2] << 8 | 0x04)); break;
	case 3: FOUR_BIT_LED_Send16(((uint16_t)SEG_CODE[digit3] << 8 | 0x02)); break;
	case 4: FOUR_BIT_LED_Send16(((uint16_t)SEG_CODE[digit4] << 8 | 0x01)); break;
	default: return;
	}
	if (digit < 4){
		digit++;
	}
	else digit = 1;
}

fdvsdv
