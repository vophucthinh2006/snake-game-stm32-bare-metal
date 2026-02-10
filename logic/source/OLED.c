#include "OLED.h"

uint8_t OLED_BYTE[oled_x * (oled_y / 8)];

void OLED_Init(void){
	uint8_t oled_init_cmd[32];
	uint8_t cmd_length = 0;

	oled_init_cmd[cmd_length++] = Display_On_Off(LOW);
	//oled_init_cmd[cmd_length++] = Set_Page_Address(0);
	oled_init_cmd[cmd_length++] = Contrast_Control_Register_On();
	oled_init_cmd[cmd_length++] = Set_Contrast_Control_Register(0xFF);
	oled_init_cmd[cmd_length++] = Set_Segment_Re_Map(HIGH);
	oled_init_cmd[cmd_length++] = Set_Normal_Reverse_Display(LOW);
	oled_init_cmd[cmd_length++] = Multiplex_Ration_On();
	oled_init_cmd[cmd_length++] = Set_Multiplex_Ration(64);
	oled_init_cmd[cmd_length++] = DC_DC_Control_On();
	oled_init_cmd[cmd_length++] = Set_DC_DC_Control(HIGH);
	oled_init_cmd[cmd_length++] = Set_Pump_Voltage_Value(EIGHT_POINT_ZERO);
	oled_init_cmd[cmd_length++] = Set_Common_Output_Scan_Direction(HIGH);
	oled_init_cmd[cmd_length++] = Display_Offset_On();
	oled_init_cmd[cmd_length++] = Set_Display_Offset(0x00);
	oled_init_cmd[cmd_length++] = Display_Clock_Divide_Ratio_On();
	oled_init_cmd[cmd_length++] = Set_Display_Clock_Divide_Ratio(8, SH1106_FREQUENCY_MINUS_25_PERCENT);
	oled_init_cmd[cmd_length++] = Dis_Charge_Pre_Charge_Period_On();
	oled_init_cmd[cmd_length++] = Set_Dis_Charge_Pre_Charge_Period(1, 0xF);
	oled_init_cmd[cmd_length++] = Common_Pads_Hardware_Configuration_On();
	oled_init_cmd[cmd_length++] = Set_Common_Pads_Hardware_Configuration(HIGH);
	oled_init_cmd[cmd_length++] = VCOM_Deselect_Level_On();
	oled_init_cmd[cmd_length++] = Set_VCOM_Deselect_Level(64);
	oled_init_cmd[cmd_length++] = Set_Display_Start_Line(0);
	oled_init_cmd[cmd_length++] = Display_On_Off(HIGH);

	SH1106_I2C_Transmit(SH1106_TYPE_cmd, oled_init_cmd, cmd_length);
};

void OLED_Set_Pixel(uint8_t x, uint8_t y, OLED_COLOR_t color){
	if ((x >= oled_x) || (y >= oled_y)){
		return;
	}
	uint8_t real_x = oled_x - 1 - x;
	uint8_t real_y = oled_y - 1 - y;
	uint16_t byte = real_x + ((real_y/8) * oled_x);

	if (color == WHITE){
		OLED_BYTE[byte] |= (1 << (real_y % 8));
	}
	else{
		OLED_BYTE[byte] &= ~(1 << (real_y % 8));
	}
}

void OLED_Set_All(void){
	for (int byte = 0; byte < (8 * oled_x); byte++){
		OLED_BYTE[byte] = 0xFF;
	}
}

void OLED_Clear_All(void){
	for (int byte = 0; byte < (8 * oled_x); byte++){
		OLED_BYTE[byte] = 0x00;
	}
}

void OLED_Update_Screen(void){
	uint8_t oled_update[4];

	for (uint8_t page = 0; page < 8; page++){
		uint8_t update_length = 0;

		oled_update[update_length++] = Set_Page_Address(page);
		oled_update[update_length++] = Set_Lower_Column_Address(0b0010);
		oled_update[update_length++] = Set_Higher_Column_Address(0b0000);


		SH1106_I2C_Transmit(SH1106_TYPE_cmd, oled_update, 3);
		SH1106_I2C_Transmit(SH1106_TYPE_data, &OLED_BYTE[page * oled_x], oled_x);
	}
}
void OLED_Update_Page(uint8_t page){
	uint8_t oled_update[4];
	uint8_t update_length = 0;

	oled_update[update_length++] = Set_Page_Address(page);
	oled_update[update_length++] = Set_Lower_Column_Address(0b0010);
	oled_update[update_length++] = Set_Higher_Column_Address(0b0000);

	SH1106_I2C_Transmit(SH1106_TYPE_cmd, oled_update, 3);
	SH1106_I2C_Transmit(SH1106_TYPE_data, &OLED_BYTE[page * oled_x], oled_x);
}










brsdb



