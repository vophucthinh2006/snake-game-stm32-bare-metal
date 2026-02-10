#ifndef __SH1106_H
#define __SH1106_H
#include <stdint.h>
#include "I2C.h"

//PUMP VOLTAGE VALUE
typedef enum{
	SIX_POINT_FOUR   = 0b00,
	SEVEN_POINT_FOUR = 0b01,
	EIGHT_POINT_ZERO = 0b10,
	NINE_POINT_ZERO  = 0b11
}SH1106_PUMP_VOLTAGE_t;

//SEGMENT REMAP
typedef enum{
	LOW = 0,
	HIGH = 1
}SH1106_LOW_HIGH_t;

//OSCILLATOR FREQUENCY
typedef enum{
	SH1106_FREQUENCY_MINUS_25_PERCENT = 0b0000,
	SH1106_FREQUENCY_MINUS_20_PERCENT = 0b0001,
	SH1106_FREQUENCY_MINUS_15_PERCENT = 0b0010,
	SH1106_FREQUENCY_MINUS_10_PERCENT = 0b0011,
	SH1106_FREQUENCY_MINUS_5_PERCENT  = 0b0100,
	SH1106_FREQUENCY_FOSC             = 0b0101,
	SH1106_FREQUENCY_PLUS_5_PERCENT   = 0b0110,
	SH1106_FREQUENCY_PLUS_10_PERCENT  = 0b0111,
	SH1106_FREQUENCY_PLUS_15_PERCENT  = 0b1000,
	SH1106_FREQUENCY_PLUS_20_PERCENT  = 0b1001,
	SH1106_FREQUENCY_PLUS_25_PERCENT  = 0b1010,
	SH1106_FREQUENCY_PLUS_30_PERCENT  = 0b1011,
	SH1106_FREQUENCY_PLUS_35_PERCENT  = 0b1100,
	SH1106_FREQUENCY_PLUS_40_PERCENT  = 0b1101,
	SH1106_FREQUENCY_PLUS_45_PERCENT  = 0b1110,
	SH1106_FREQUENCY_PLUS_50_PERCENT  = 0b1111,
}SH1106_FREQUENCY_t;

//I2C TRANSMIT SH1106
typedef enum{
	SH1106_TYPE_cmd  = 0X00,
	SH1106_TYPE_data = 0x40
}SH1106_TYPE_t;

uint8_t Set_Lower_Column_Address (uint8_t low_column);
uint8_t Set_Higher_Column_Address (uint8_t high_column);
uint8_t Set_Pump_Voltage_Value (SH1106_PUMP_VOLTAGE_t voltage);
uint8_t Set_Display_Start_Line (uint16_t line);
uint8_t Contrast_Control_Register_On (void);
uint8_t Set_Contrast_Control_Register (uint8_t contrast);
uint8_t Set_Segment_Re_Map (SH1106_LOW_HIGH_t segment);
uint8_t Set_Entire_Display_On_Off (SH1106_LOW_HIGH_t on_off);
uint8_t Set_Normal_Reverse_Display (SH1106_LOW_HIGH_t display);
uint8_t Multiplex_Ration_On (void);
uint8_t Set_Multiplex_Ration (uint8_t mutiplex_ration);
uint8_t DC_DC_Control_On (void);
uint8_t Set_DC_DC_Control (SH1106_LOW_HIGH_t on_off);
uint8_t Display_On_Off (SH1106_LOW_HIGH_t display);
uint8_t Set_Page_Address (uint8_t page);
uint8_t Set_Common_Output_Scan_Direction (SH1106_LOW_HIGH_t direction);
uint8_t Display_Offset_On (void);
uint8_t Set_Display_Offset (uint8_t display_offset);
uint8_t Display_Clock_Divide_Ratio_On (void);
uint8_t Set_Display_Clock_Divide_Ratio (uint8_t divide_ration, SH1106_FREQUENCY_t oscillator_frequency);
uint8_t Dis_Charge_Pre_Charge_Period_On (void);
uint8_t Set_Dis_Charge_Pre_Charge_Period (uint8_t pre_charge_DCLKs, uint8_t dis_charge_DCLKs);
uint8_t Common_Pads_Hardware_Configuration_On (void);
uint8_t Set_Common_Pads_Hardware_Configuration (SH1106_LOW_HIGH_t mode);
uint8_t VCOM_Deselect_Level_On (void);
uint8_t Set_VCOM_Deselect_Level (uint8_t level);
uint8_t Read_Modify_Write (void);
uint8_t End (void);
uint8_t NOP (void);
void SH1106_I2C_Transmit(SH1106_TYPE_t type, uint8_t *cmd_data,  uint8_t length);

#endif

FQWEAF
