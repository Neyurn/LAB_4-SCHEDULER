/*
 * lab_3.c
 *
 *  Created on: Nov 29, 2025
 *      Author: Khôi Nguyên
 */

#include "lab_3.h"

#define TIME_MIN 1
#define TIME_MAX 99


uint8_t red_time = RED_TIME;
uint8_t yel_time = YEL_TIME;
uint8_t gre_time = GRE_TIME;

uint16_t X_clock = 0;
uint16_t Y_clock = 0;

uint8_t tfl_status = INIT_TFL;

static uint16_t clock_counter = 0;
static uint16_t state_counter = 0;
static uint16_t blink_counter =0;


static uint8_t red_tmp_time = RED_TIME;
static uint8_t yel_tmp_time = YEL_TIME;
static uint8_t gre_tmp_time = GRE_TIME;

static uint8_t clamp(int16_t val){
    if (val < TIME_MIN) return TIME_MIN;
    if (val > TIME_MAX) return TIME_MAX;
    return (uint8_t)val;
}



//-----[FSM]-----------
void fsm_traffic_light(void){
	switch (tfl_status) {
	//---------------
		case INIT_TFL:
			tfl_status = AUTO_RED_GRE;
			X_clock = red_time ;
			Y_clock = gre_time ;
			state_counter = yel_time *100;
			clock_counter = 100; //1000 ms / 10 = 100 ticks
			break;

		case AUTO_RED_GRE:
			red_green();
			if(state_counter >0) state_counter--;
			if(clock_counter >0) clock_counter--;

			if(clock_counter == 0){
				if(X_clock > 0) X_clock--;
				if(Y_clock > 0) Y_clock--;
				clock_counter = 100;
			}

			if(state_counter == 0){
				tfl_status = AUTO_RED_YEL;
				X_clock = yel_time; //( red_time = yel_time + gre_time)
				Y_clock = yel_time;
				state_counter = yel_time*100;
				clock_counter = 100;
			}

			//chuyen mode
			if(isButtonPressed(&button0)){
				tfl_status = CFG_RED;
				disable_all_traffic_light();
				init_cfg_red();
			}

			break;
		case AUTO_RED_YEL:
			red_yel();
			if(state_counter >0) state_counter--;
			if(clock_counter >0) clock_counter--;

			if(clock_counter == 0){
				if(X_clock > 0) X_clock--;
				if(Y_clock > 0) Y_clock--;
				clock_counter = 100;
			}

			if(state_counter == 0){
				tfl_status = AUTO_GRE_RED;
				X_clock = gre_time;
				Y_clock = red_time;
				state_counter = gre_time*100;
				clock_counter = 100;
			}

			//chuyen mode
			if(isButtonPressed(&button0)){
				tfl_status = CFG_RED;
				disable_all_traffic_light();
				init_cfg_red();
			}

			break;
		case AUTO_GRE_RED:
			green_red();
			if(state_counter >0) state_counter--;
			if(clock_counter >0) clock_counter--;

			if(clock_counter == 0){
				if(X_clock > 0) X_clock--;
				if(Y_clock > 0) Y_clock--;
				clock_counter = 100;
			}

			if(state_counter == 0){
				tfl_status = AUTO_YEL_RED;
				X_clock = yel_time;
				Y_clock = yel_time;
				state_counter = yel_time*100;
				clock_counter = 100;
			}

			//chuyen mode
			if(isButtonPressed(&button0)){
				tfl_status = CFG_RED;
				disable_all_traffic_light();
				init_cfg_red();
			}

			break;
		case AUTO_YEL_RED:
			yel_red();
			if(state_counter >0) state_counter--;
			if(clock_counter >0) clock_counter--;

			if(clock_counter == 0){
				if(X_clock > 0) X_clock--;
				if(Y_clock > 0) Y_clock--;
				clock_counter = 100;
			}

			if(state_counter == 0){
				tfl_status = AUTO_RED_GRE;
				X_clock = red_time;
				Y_clock = gre_time;
				state_counter = gre_time*100;
				clock_counter = 100;
			}

			//chuyen mode
			if(isButtonPressed(&button0)){
				tfl_status = CFG_RED;
				disable_all_traffic_light();
				init_cfg_red();
			}

			break;
		case CFG_RED:
			cfg_red_run();

			if(isButtonPressed(&button0)){
				tfl_status = CFG_YEL;
				init_cfg_yel();
			}

			if(isButtonPressed(&button1)){
	            uint8_t min_red = yel_time + TIME_MIN;
	            if(min_red > TIME_MAX) min_red = TIME_MAX;

	            red_tmp_time++;
	            if (red_tmp_time > TIME_MAX || red_tmp_time < min_red) {
	                red_tmp_time = min_red;
	            }

	            X_clock = red_tmp_time;
			}

			if(isButtonPressed(&button2)){
				confirm_red_time();
				init_cfg_red();
				tfl_status = INIT_TFL;
			}

			break;
		case CFG_YEL:
			cfg_yel_run();

			if(isButtonPressed(&button0)){
				tfl_status = CFG_GRE;
				init_cfg_gre();
			}

			if(isButtonPressed(&button1)){
                yel_tmp_time++;
                if (yel_tmp_time > TIME_MAX || yel_tmp_time < TIME_MIN ){
                    yel_tmp_time = TIME_MIN;
                }

                X_clock = yel_tmp_time;
			}

	        if (isButtonPressed(&button2)) {
	            confirm_yel_time();
	            init_cfg_yel();
				tfl_status = INIT_TFL;
	        }
	        break;
		case CFG_GRE:
			cfg_gre_run();

			if(isButtonPressed(&button0)){
				tfl_status = INIT_TFL;
				disable_all_traffic_light();

			}

			if(isButtonPressed(&button1)){
                gre_tmp_time++;
                if (gre_tmp_time > TIME_MAX || gre_tmp_time < TIME_MIN ){
                    gre_tmp_time = TIME_MIN;
                }

                X_clock = gre_tmp_time;
			}

	        if (isButtonPressed(&button2)) {
	            confirm_gre_time();
	            init_cfg_gre();
				tfl_status = INIT_TFL;
	        }
	        break;

		default:
			break;
	}
}

//----MODE_1: AUTO MODE ( NORMAL MODE)------------------------------------
void red_green(void){
	HAL_GPIO_WritePin(RED_X_GPIO_Port, RED_X_Pin , 0);
	HAL_GPIO_WritePin(YEL_X_GPIO_Port, YEL_X_Pin , 1);
	HAL_GPIO_WritePin(GRE_X_GPIO_Port, GRE_X_Pin , 1);

	HAL_GPIO_WritePin(RED_Y_GPIO_Port, RED_Y_Pin , 1);
	HAL_GPIO_WritePin(YEL_Y_GPIO_Port, YEL_Y_Pin , 1);
	HAL_GPIO_WritePin(GRE_Y_GPIO_Port, GRE_Y_Pin , 0);
}
void red_yel(void){
	HAL_GPIO_WritePin(RED_X_GPIO_Port, RED_X_Pin , 0);
	HAL_GPIO_WritePin(YEL_X_GPIO_Port, YEL_X_Pin , 1);
	HAL_GPIO_WritePin(GRE_X_GPIO_Port, GRE_X_Pin , 1);

	HAL_GPIO_WritePin(RED_Y_GPIO_Port, RED_Y_Pin , 1);
	HAL_GPIO_WritePin(YEL_Y_GPIO_Port, YEL_Y_Pin , 0);
	HAL_GPIO_WritePin(GRE_Y_GPIO_Port, GRE_Y_Pin , 1);
}
void green_red(void){
	HAL_GPIO_WritePin(RED_X_GPIO_Port, RED_X_Pin , 1);
	HAL_GPIO_WritePin(YEL_X_GPIO_Port, YEL_X_Pin , 1);
	HAL_GPIO_WritePin(GRE_X_GPIO_Port, GRE_X_Pin , 0);

	HAL_GPIO_WritePin(RED_Y_GPIO_Port, RED_Y_Pin , 0);
	HAL_GPIO_WritePin(YEL_Y_GPIO_Port, YEL_Y_Pin , 1);
	HAL_GPIO_WritePin(GRE_Y_GPIO_Port, GRE_Y_Pin , 1);
}
void yel_red(void){
	HAL_GPIO_WritePin(RED_X_GPIO_Port, RED_X_Pin , 1);
	HAL_GPIO_WritePin(YEL_X_GPIO_Port, YEL_X_Pin , 0);
	HAL_GPIO_WritePin(GRE_X_GPIO_Port, GRE_X_Pin , 1);

	HAL_GPIO_WritePin(RED_Y_GPIO_Port, RED_Y_Pin , 0);
	HAL_GPIO_WritePin(YEL_Y_GPIO_Port, YEL_Y_Pin , 1);
	HAL_GPIO_WritePin(GRE_Y_GPIO_Port, GRE_Y_Pin , 1);
}
void disable_all_traffic_light(void){
	HAL_GPIO_WritePin(RED_X_GPIO_Port, RED_X_Pin , 1);
	HAL_GPIO_WritePin(YEL_X_GPIO_Port, YEL_X_Pin , 1);
	HAL_GPIO_WritePin(GRE_X_GPIO_Port, GRE_X_Pin , 1);

	HAL_GPIO_WritePin(RED_Y_GPIO_Port, RED_Y_Pin , 1);
	HAL_GPIO_WritePin(YEL_Y_GPIO_Port, YEL_Y_Pin , 1);
	HAL_GPIO_WritePin(GRE_Y_GPIO_Port, GRE_Y_Pin , 1);
}


//----MODE 2/3/4 : CONFIG MODE--------------------------------------------------

void init_cfg_red(void){
	red_tmp_time = red_time;
	turn_all_red();
	blink_counter = 25;

	X_clock = red_tmp_time;
	Y_clock = 2;

}
void init_cfg_yel(void){
	yel_tmp_time = yel_time;
	turn_all_yel();
	blink_counter = 25;

	X_clock = yel_tmp_time;
	Y_clock = 3;
}
void init_cfg_gre(void){
	gre_tmp_time = gre_time;
	turn_all_gre();
	blink_counter = 25;

	X_clock = gre_tmp_time;
	Y_clock = 4;
}

void cfg_red_run(void){
	if(blink_counter > 0) --blink_counter;

	if(blink_counter == 0){
		blink_counter = 25;
		HAL_GPIO_TogglePin(RED_X_GPIO_Port, RED_X_Pin);
		HAL_GPIO_TogglePin(RED_Y_GPIO_Port, RED_Y_Pin);
	}
}
void cfg_yel_run(void){
	if(blink_counter > 0) --blink_counter;

	if(blink_counter == 0){
		blink_counter = 25;
		HAL_GPIO_TogglePin(YEL_X_GPIO_Port, YEL_X_Pin);
		HAL_GPIO_TogglePin(YEL_Y_GPIO_Port, YEL_Y_Pin);
	}
}
void cfg_gre_run(void){
	if(blink_counter > 0) --blink_counter;

	if(blink_counter == 0){
		blink_counter = 25;
		HAL_GPIO_TogglePin(GRE_X_GPIO_Port, GRE_X_Pin);
		HAL_GPIO_TogglePin(GRE_Y_GPIO_Port, GRE_Y_Pin);
	}
}

void confirm_red_time(void){
	red_tmp_time = clamp(red_tmp_time);
    int16_t calc_gre = (int16_t)red_tmp_time - (int16_t)yel_time;

	calc_gre = clamp(calc_gre);

    gre_time = (uint8_t)calc_gre;
	red_time = gre_time + yel_time;
	red_time = clamp(red_time);


}
void confirm_yel_time(void){
	yel_tmp_time = clamp(yel_tmp_time);
    int16_t calc_gre = (int16_t)red_time - (int16_t)yel_tmp_time;

	calc_gre = clamp(calc_gre);

    gre_time = (uint8_t)calc_gre;
	yel_time = yel_tmp_time;
	red_time = gre_time + yel_time;
	red_time = clamp(red_time);
}
void confirm_gre_time(void){
    gre_tmp_time = clamp(gre_tmp_time);
    int16_t calc_red = (int16_t)gre_tmp_time + (int16_t)yel_time;

    if (calc_red > TIME_MAX) {
        red_time = TIME_MAX;
        gre_time = red_time - yel_time;
        gre_time = clamp(gre_time);
    } else if (calc_red < TIME_MIN) {
        red_time = TIME_MIN;
        gre_time = red_time - yel_time;
        gre_time = clamp(gre_time);
    } else {
        gre_time = gre_tmp_time;
        red_time = (uint8_t)calc_red;
    }
}


void turn_all_red(void){
	HAL_GPIO_WritePin(RED_X_GPIO_Port, RED_X_Pin , 0);
	HAL_GPIO_WritePin(YEL_X_GPIO_Port, YEL_X_Pin , 1);
	HAL_GPIO_WritePin(GRE_X_GPIO_Port, GRE_X_Pin , 1);

	HAL_GPIO_WritePin(RED_Y_GPIO_Port, RED_Y_Pin , 0);
	HAL_GPIO_WritePin(YEL_Y_GPIO_Port, YEL_Y_Pin , 1);
	HAL_GPIO_WritePin(GRE_Y_GPIO_Port, GRE_Y_Pin , 1);
}
void turn_all_yel(void){
	HAL_GPIO_WritePin(RED_X_GPIO_Port, RED_X_Pin , 1);
	HAL_GPIO_WritePin(YEL_X_GPIO_Port, YEL_X_Pin , 0);
	HAL_GPIO_WritePin(GRE_X_GPIO_Port, GRE_X_Pin , 1);

	HAL_GPIO_WritePin(RED_Y_GPIO_Port, RED_Y_Pin , 1);
	HAL_GPIO_WritePin(YEL_Y_GPIO_Port, YEL_Y_Pin , 0);
	HAL_GPIO_WritePin(GRE_Y_GPIO_Port, GRE_Y_Pin , 1);
}
void turn_all_gre(void){
	HAL_GPIO_WritePin(RED_X_GPIO_Port, RED_X_Pin , 1);
	HAL_GPIO_WritePin(YEL_X_GPIO_Port, YEL_X_Pin , 1);
	HAL_GPIO_WritePin(GRE_X_GPIO_Port, GRE_X_Pin , 0);

	HAL_GPIO_WritePin(RED_Y_GPIO_Port, RED_Y_Pin , 1);
	HAL_GPIO_WritePin(YEL_Y_GPIO_Port, YEL_Y_Pin , 1);
	HAL_GPIO_WritePin(GRE_Y_GPIO_Port, GRE_Y_Pin , 0);
}
