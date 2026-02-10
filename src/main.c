#include "ADC.h"
#include "AFIO.h"
#include "GPIO.h"
#include "I2C.h"
#include "RCC.h"
#include "TIM.h"
#include "SH1106.h"
#include "FOUR_BIT_LED.h"
#include "OLED.h"
#include "SNAKE.h"
#include "bitmap.h"

int main (void){
	//RCC_Set_72MHz();
	RCC_Enable(RCC_PORTA);
	RCC_Enable(RCC_PORTB);
	RCC_Enable(RCC_I2C1);
	RCC_Enable(RCC_TIM2);
	RCC_Enable(RCC_TIM3);
	RCC_Enable(RCC_TIM4);
	RCC_Enable(RCC_ADC1);
	RCC_Enable(RCC_ADC2);

	GPIO_Config(GPIO_PORTB, 0, GPIO_CNF_IN_PD, GPIO_MODE_IN);
	GPIO_Config(GPIO_PORTB, 1, GPIO_CNF_IN_PD, GPIO_MODE_IN);

	I2C_Init(I2C1, 8, I2C_SPEED_STANDARD);

	TIM_Interrupt_Init(TIM3, 10);
	TIM_Random_Init(TIM2);

	ADC_Number_Conversation(ADC1, 1);
	ADC_Init(ADC1, 0, ADC_SAMPLE_TIME_239_5, 1, ADC_MODE_CONTINUOUS);
	GPIO_Config(GPIO_PORTA, 0, GPIO_CNF_IN_ANA, GPIO_MODE_IN);


	ADC_Number_Conversation(ADC2, 1);
	ADC_Init(ADC2, 1, ADC_SAMPLE_TIME_239_5, 1, ADC_MODE_CONTINUOUS);
	GPIO_Config(GPIO_PORTA, 1, GPIO_CNF_IN_ANA, GPIO_MODE_IN);

	FOUR_BIT_LED_Config(GPIO_PORTA, 3, 4, 2);
	GPIO_Config(GPIO_PORTA, 2, GPIO_CNF_OUT_PP, GPIO_MODE_OUT_50M);
	GPIO_Config(GPIO_PORTA, 3, GPIO_CNF_OUT_PP, GPIO_MODE_OUT_50M);
	GPIO_Config(GPIO_PORTA, 4, GPIO_CNF_OUT_PP, GPIO_MODE_OUT_50M);

	OLED_Init();

	snake_state = SNAKE_STATE_LOBBY;

	while (1){
		if (snake_state != SNAKE_STATE_END)      Score_Scan();
		else if (snake_state == SNAKE_STATE_END) Highscore_Scan();

		if (snake_state == SNAKE_STATE_PLAY){
			SNAKE_Read_Joystick();
		}
		if (snake_tick == 1){
			snake_tick = 0;
			OLED_Clear_All();

			switch(snake_state){

			case SNAKE_STATE_LOBBY:
				if (GPIO_Read_Pin(GPIO_PORTB, 0) == 1){
					button_pressed = 1;
					button_start = 1;
					break;
				}
				if ((button_stable == 1) && (button_start == 1)){
					button_stable =0;
					button_start = 0;
					snake_state = SNAKE_STATE_START;
					break;
				}
				if (snake_lobby == 0){
					snake_lobby = 1;
					OLED_Convert_CF1_To_Buffer(SNAKE_LOBBY_1, OLED_BYTE, oled_x, oled_y);
				}
				else{
					snake_lobby = 0;
					OLED_Convert_CF1_To_Buffer(SNAKE_LOBBY_2, OLED_BYTE, oled_x, oled_y);
				}
				score = 0;
				highscore_flag = 0;
				OLED_Update_Screen();
				break;

			case SNAKE_STATE_START:
				SNAKE_Init();
				SNAKE_Draw_Wall();
				Food_Spawn();
				OLED_Update_Screen();

				snake_state = SNAKE_STATE_PLAY;

				break;

			case SNAKE_STATE_PLAY:
				if (GPIO_Read_Pin(GPIO_PORTB, 1) == 1){
					button_pressed = 1;
					button_pause = 1;
					break;
				}
				if ((button_stable == 1) && (button_pause == 1)){
					button_stable = 0;
					button_pause = 0;
					snake_state = SNAKE_STATE_PAUSE;
					break;
				}
				SNAKE_Move();
				SNAKE_Draw_Self();

				Food_Blink();

				if (SNAKE_Eat_Food() == EATEN){
					score++;
					Food_Spawn();
				}

				if ((SNAKE_Eat_Wall() == EATEN) || (SNAKE_Eat_Self() == EATEN)){
					snake_state = SNAKE_STATE_END;
					break;
				}
				SNAKE_Draw_Wall();

				OLED_Update_Screen();
				break;

			case SNAKE_STATE_PAUSE:
				if (GPIO_Read_Pin(GPIO_PORTB, 0) == 1){
					button_pressed = 1;
					button_start = 1;
					break;
				}
				if (GPIO_Read_Pin(GPIO_PORTB, 1) == 1){
					button_pressed = 1;
					button_pause = 1;
					break;
				}
				if ((button_stable == 1) && (button_start == 1)){
					button_stable = 0;
					button_start = 0;
					snake_state = SNAKE_STATE_LOBBY;
					break;
				}
				if ((button_stable == 1) && (button_pause == 1)){
					button_stable = 0;
					button_pause = 0;
					snake_state = SNAKE_STATE_PLAY;
					break;
				}
				if (snake_pause == 0){
					snake_pause = 1;
					OLED_Convert_CF1_To_Buffer(SNAKE_PAUSE_1, OLED_BYTE, oled_x, oled_y);
				}
				else{
					snake_pause = 0;
					OLED_Convert_CF1_To_Buffer(SNAKE_PAUSE_2, OLED_BYTE, oled_x, oled_y);
				}

				OLED_Update_Screen();
				break;

			case SNAKE_STATE_END:
				if (GPIO_Read_Pin(GPIO_PORTB, 0) == 1){
					button_pressed = 1;
					button_start = 1;
					break;
				}
				if ((button_stable == 1) && (button_start == 1)){
					button_stable = 0;
					button_start = 0;
					snake_state = SNAKE_STATE_LOBBY;
					break;
				}

				if (score > highscore){
					highscore_flag = 1;
					highscore = score;
				}

				if (highscore_flag == 1){
					if (snake_end == 0){
						snake_end = 1;
						OLED_Convert_CF1_To_Buffer(SNAKE_END_HIGHSCORE, OLED_BYTE, oled_x, oled_y);
					}
					else {
						snake_end = 0;
						OLED_Convert_CF1_To_Buffer(SNAKE_END_2, OLED_BYTE, oled_x, oled_y);
					}

				}
				else{
					if (snake_end == 0){
						snake_end = 1;
						OLED_Convert_CF1_To_Buffer(SNAKE_END_1, OLED_BYTE, oled_x, oled_y);
					}
					else {
						snake_end = 0;
						OLED_Convert_CF1_To_Buffer(SNAKE_END_2, OLED_BYTE, oled_x, oled_y);
					}
				}

				OLED_Update_Screen();
				break;

			default:
				return SNAKE_STATE_LOBBY;
			}
		}
	}
}
