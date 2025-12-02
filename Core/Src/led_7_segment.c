/*
 * led_7_segment.c
 *
 *  Created on: Nov 28, 2025
 *      Author: Khôi Nguyên
 */


#include "led_7_segment.h"

uint8_t clock_status = SEG0;

const uint8_t matrix_7SEG[10] = {
		0x3F, //0: a b c d e f
		0x06, //1:   b c
		0x5B, //2: a b   d e   g
		0x4F, //3: a b c d     g
		0x66, //4:   b c     f g
		0x6D, //5: a   c d   f g
		0x7D, //6: a   c d e f g
		0x07, //7: a b c
		0x7F, //8: a b c d e f g
		0x6F, //9: a b c d   f g
};

uint8_t X_clock_buffer[2] = {0,0};
uint8_t Y_clock_buffer[2] = {0,0};

void update_clock_buffer(){
	X_clock_buffer[0] = (X_clock) / 10;
	X_clock_buffer[1] = (X_clock) % 10;
	Y_clock_buffer[0] = (Y_clock) / 10;
	Y_clock_buffer[1] = (Y_clock) % 10;
}

void display_clock(){
	update_clock_buffer();
	switch (clock_status) {
		case SEG0:
			enable_num(0);
			display_X_num(matrix_7SEG[X_clock_buffer[0]]);
			clock_status = SEG1;
			break;
		case SEG1:
			enable_num(1);
			display_X_num(matrix_7SEG[X_clock_buffer[1]]);
			clock_status = SEG2;
			break;
		case SEG2:
			enable_num(2);
			display_Y_num(matrix_7SEG[Y_clock_buffer[0]]);
			clock_status = SEG3;
			break;
		case SEG3:
			enable_num(3);
			display_Y_num(matrix_7SEG[Y_clock_buffer[1]]);
			clock_status = SEG0;
			break;
		default:
			break;
	}
}

void display_X_num(uint8_t num){
	HAL_GPIO_WritePin(SEG0_0_GPIO_Port, SEG0_0_Pin, (num & (1<<0)) ? 1:0 );
	HAL_GPIO_WritePin(SEG0_1_GPIO_Port, SEG0_1_Pin, (num & (1<<1)) ? 1:0 );
	HAL_GPIO_WritePin(SEG0_2_GPIO_Port, SEG0_2_Pin, (num & (1<<2)) ? 1:0 );
	HAL_GPIO_WritePin(SEG0_3_GPIO_Port, SEG0_3_Pin, (num & (1<<3)) ? 1:0 );
	HAL_GPIO_WritePin(SEG0_4_GPIO_Port, SEG0_4_Pin, (num & (1<<4)) ? 1:0 );
	HAL_GPIO_WritePin(SEG0_5_GPIO_Port, SEG0_5_Pin, (num & (1<<5)) ? 1:0 );
	HAL_GPIO_WritePin(SEG0_6_GPIO_Port, SEG0_6_Pin, (num & (1<<6)) ? 1:0 );
}

void display_Y_num(uint8_t num){
	HAL_GPIO_WritePin(SEG1_0_GPIO_Port, SEG1_0_Pin, (num & (1<<0)) ? 1:0 );
	HAL_GPIO_WritePin(SEG1_1_GPIO_Port, SEG1_1_Pin, (num & (1<<1)) ? 1:0 );
	HAL_GPIO_WritePin(SEG1_2_GPIO_Port, SEG1_2_Pin, (num & (1<<2)) ? 1:0 );
	HAL_GPIO_WritePin(SEG1_3_GPIO_Port, SEG1_3_Pin, (num & (1<<3)) ? 1:0 );
	HAL_GPIO_WritePin(SEG1_4_GPIO_Port, SEG1_4_Pin, (num & (1<<4)) ? 1:0 );
	HAL_GPIO_WritePin(SEG1_5_GPIO_Port, SEG1_5_Pin, (num & (1<<5)) ? 1:0 );
	HAL_GPIO_WritePin(SEG1_6_GPIO_Port, SEG1_6_Pin, (num & (1<<6)) ? 1:0 );
}

void disable_all(){
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
}

void enable_num(uint8_t idx){
	switch (idx) {
		case 0:
			disable_all();
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			break;
		case 1:
			disable_all();
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			break;
		case 2:
			disable_all();
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			break;
		case 3:
			disable_all();
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
			break;
		default:
			break;
	}
}
