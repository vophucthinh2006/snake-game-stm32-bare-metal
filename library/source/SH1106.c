#include "SH1106.h"

uint8_t Set_Lower_Column_Address (uint8_t low_column){
	return (0b00000000 | (0b00001111 & low_column));
}
uint8_t Set_Higher_Column_Address (uint8_t high_column){
	return (0b00010000 | (0b00001111 & high_column));
}
uint8_t Set_Pump_Voltage_Value (SH1106_PUMP_VOLTAGE_t voltage){
	return (0b00110000 | (0b00000011 & voltage));
}
uint8_t Set_Display_Start_Line (uint16_t line){
	return (0b01000000 | (0b00111111 & line));
}
uint8_t Contrast_Control_Register_On (void){
	return 0b10000001;
}
uint8_t Set_Contrast_Control_Register (uint8_t contrast){
	if ((contrast >= 0b00000000) && (contrast <= 0b11111111)){
		return contrast;
	}
	else {
		return 0x00;
	}
}
uint8_t Set_Segment_Re_Map (SH1106_LOW_HIGH_t segment){
	return (0b1010000 | (0b00000001 & segment));
}
uint8_t Set_Entire_Display_On_Off (SH1106_LOW_HIGH_t on_off){
	return (0b10100100 | (0b00000001 & on_off));
}
uint8_t Set_Normal_Reverse_Display (SH1106_LOW_HIGH_t display){
	return (0b10100110 | (0b00000001 & display));
}
uint8_t Multiplex_Ration_On (void){
	return 0b10101000;
}
uint8_t Set_Multiplex_Ration (uint8_t mutiplex_ration){
	if (((mutiplex_ration - 1) >= 0b00000000) && ((mutiplex_ration -1) <= 0b00111111)){
		return (mutiplex_ration - 1);
	}
	else {
		return 0x00;
	}
}
uint8_t DC_DC_Control_On (void){
	return 0b10101101;
}
uint8_t Set_DC_DC_Control (SH1106_LOW_HIGH_t on_off){
	return (0b10001010 | (0b00000001 & on_off));
}
uint8_t Display_On_Off (SH1106_LOW_HIGH_t display){
	return (0b10101110 | (0b00000001 & display));
}
uint8_t Set_Page_Address (uint8_t page){
	if ((page >=0) && (page <= 7)){
		return (0b10110000 | (0b00001111 & page));
	}
	else {
		return 0x00;
	}
}
uint8_t Set_Common_Output_Scan_Direction (SH1106_LOW_HIGH_t direction){
	if (direction == HIGH){
		return 0b11001000;
	}
	else {
		return 0b11000000;
	}
}
uint8_t Display_Offset_On (void){
	return 0b11010011;
}
uint8_t Set_Display_Offset (uint8_t display_offset){
	if (((display_offset) >= 0) && ((display_offset) <= 63)){
		return display_offset;
	}
	else{
		return 0x00;
	}
}
uint8_t Display_Clock_Divide_Ratio_On (void){
	return 0b11010101;
}
uint8_t Set_Display_Clock_Divide_Ratio (uint8_t divide_ration, SH1106_FREQUENCY_t oscillator_frequency){
	return ((0b11110000 & divide_ration) | (0b00001111 & oscillator_frequency));
}
uint8_t Dis_Charge_Pre_Charge_Period_On (void){
	return 0b11011001;
}
uint8_t Set_Dis_Charge_Pre_Charge_Period (uint8_t pre_charge_DCLKs, uint8_t dis_charge_DCLKs){
	return ((0b11110000 & pre_charge_DCLKs) | (0b00001111 & dis_charge_DCLKs));
}
uint8_t Common_Pads_Hardware_Configuration_On (void){
	return 0b11011010;
}
uint8_t Set_Common_Pads_Hardware_Configuration (SH1106_LOW_HIGH_t mode){
	if (mode == HIGH){
		return 0b00010010;
	}
	else{
		return 0b00000010;
	}
}
uint8_t VCOM_Deselect_Level_On (void){
	return 0b11011011;
}
uint8_t Set_VCOM_Deselect_Level (uint8_t level){
	if ((level >= 0x00) && (level <= 0x40)){
		return level;
	}
	else {
		return 0x00;
	}
}
uint8_t Read_Modify_Write (void){
	return 0b11100000;
}
uint8_t End (void){
	return 0b11101110;
}
uint8_t NOP (void){
	return 0b11100011;
}
void SH1106_I2C_Transmit(SH1106_TYPE_t type, uint8_t *cmd_data,  uint8_t length){
	I2C_Start(I2C1);
	I2C_Transmit_Address(I2C1, 0b0111100, type, I2C_LSB_TRANSMIT);
	I2C_Master_Transmit_Data(I2C1,cmd_data, length);
	I2C_Stop(I2C1);
}
CÁDC
