/*
 * lcd_i2c.c
 *
 *  Created on: 9 Dec 2025
 *      Author: dell pro
 */


#include "lcd_i2c.h"

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void) {
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	HAL_Delay(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	HAL_Delay(50);
	lcd_send_cmd (0x01); /* clear display */
	HAL_Delay(50);
	lcd_send_cmd (0x06); /* set entry mode */
	HAL_Delay(50);
	lcd_send_cmd (0x0c); /* set display to on */
	HAL_Delay(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 0)  // Sửa thành row 0 (thay vì 1)
	{
		pos_Addr = 0x80 + col;  // Dòng 1: 0x80 + vị trí
	}
	else if(row == 1)  // Thêm điều kiện cho dòng 2
	{
		pos_Addr = 0xC0 + col;  // Dòng 2: 0xC0 + vị trí
	}
	else
	{
		pos_Addr = 0x80 + col;  // Mặc định dòng 1
	}
	lcd_send_cmd(pos_Addr);
}

void lcd_send_number(uint8_t num) {
    if (num < 10) {
        lcd_send_data(num + '0');
    } else {
        lcd_send_data((num / 10) + '0');
        lcd_send_data((num % 10) + '0');
    }
}

void updateLCDBuffer_Auto() {
	if (system_state != NORMAL_STATE) return;
	lcd_goto_XY(0,0);
	lcd_send_string("AUTO MODE");
	lcd_goto_XY(1,0);
	switch (light_state1) {
		case (RED_STATE): {
			lcd_send_string("R: ");
			lcd_goto_XY(1,3);
			lcd_send_number(Red_Counter_temp1 );
		} break;
		case (GREEN_STATE): {
			lcd_send_string("G: ");
			lcd_goto_XY(1,3);
			lcd_send_number(Green_Counter_temp1 );
		} break;
		case (YELLOW_STATE): {
				lcd_send_string("Y: ");
				lcd_goto_XY(1,3);
				lcd_send_number(Yellow_Counter_temp1);
			} break;

	}

	lcd_goto_XY(1,8);
	switch (light_state2) {
		case (RED_STATE): {
			lcd_send_string("R: ");
			lcd_goto_XY(1,11);
			lcd_send_number(Red_Counter_temp2);
		} break;

		case (GREEN_STATE): {
			lcd_send_string("G: ");
			lcd_goto_XY(1,11);
			lcd_send_number(Green_Counter_temp2 );
		} break;

		case (YELLOW_STATE): {
			lcd_send_string("Y: ");
			lcd_goto_XY(1,11);
			lcd_send_number(Yellow_Counter_temp2 );
		} break;
	}
}

void updateLCDBuffer_Manual() {
    if (system_state != MANUAL_STATE) return;

    lcd_goto_XY(0,0);
    lcd_send_string("MANUAL MODE ");

    lcd_goto_XY(1,0);
    if (light_state1 == RED_STATE) {
        lcd_send_string("RED   GREEN");
    } else {
        lcd_send_string("GREEN  RED ");
    }
}


void updateLCDBuffer_Tunning() {
	if (system_state != TUNNING_STATE) return;
	lcd_goto_XY(0,0);
	lcd_send_string("TUNNING MODE");
	lcd_goto_XY(1,0);
	lcd_send_string("M: ");
	lcd_goto_XY(1,3);
	switch (setting_state) {
		case TUNNING_RED_STATE: {
			lcd_send_string("R");
		} break;

		case TUNNING_YELLOW_STATE: {
			lcd_send_string("Y");
		} break;

		case TUNNING_GREEN_STATE: {
			lcd_send_string("G");
		} break;
	}
	lcd_goto_XY(1,8);
	lcd_send_string("N: ");
	lcd_goto_XY(1,11);
	switch (setting_state) {
		case TUNNING_RED_STATE: {
			lcd_send_number(Pre_Red_Counter);
		} break;

		case TUNNING_YELLOW_STATE: {
			lcd_send_number(Pre_Yellow_Counter);
		} break;

		case TUNNING_GREEN_STATE: {
			lcd_send_number(Pre_Green_Counter);
		} break;
	}
}


void updateLCDBuffer() {
	lcd_goto_XY(0,0);
	lcd_send_string("                ");
	lcd_goto_XY(1,0);
	lcd_send_string("                ");
	updateLCDBuffer_Auto();
	updateLCDBuffer_Manual();
	updateLCDBuffer_Tunning();
}
