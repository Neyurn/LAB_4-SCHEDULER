/*
 * tasks.c
 *
 *  Created on: Nov 19, 2025
 *      Author: Khôi Nguyên
 */

#include "tasks.h"


void blinky_led(void){
	HAL_GPIO_TogglePin(SIG_BLINK_LED_GPIO_Port, SIG_BLINK_LED_Pin);
}
void get_button_input(void){
	getKeyInput(&button0);
	getKeyInput(&button1);
	getKeyInput(&button2);
}
void control_3led(void){
	if(isButtonPressed(&button2)){
		HAL_GPIO_TogglePin(SIG_LED_RED_GPIO_Port, SIG_LED_RED_Pin);
	}
	if(isButtonPressed(&button1)){
		HAL_GPIO_TogglePin(SIG_LED_YEL_GPIO_Port, SIG_LED_YEL_Pin);
	}
//	if(isButtonPressed(&button2)){
//		HAL_GPIO_TogglePin(SIG_LED_GRE_GPIO_Port, SIG_LED_GRE_Pin);
//	}
}


void run_lab_3(void){
	getKeyInput(&button0);
	getKeyInput(&button1);
	getKeyInput(&button2);

	fsm_traffic_light();
	display_clock();
}
