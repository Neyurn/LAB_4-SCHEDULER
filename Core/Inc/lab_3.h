/*
 * lab_3.h
 *
 *  Created on: Nov 28, 2025
 *      Author: Khôi Nguyên
 */

#ifndef INC_LAB_3_H_
#define INC_LAB_3_H_

#include "main.h"
#include "button.h"
#include "led_7_segment.h"
#include "global.h"

//-----[FSM]-----------
void fsm_traffic_light(void);

//----MODE_1: AUTO MODE ( NORMAL MODE)------------------------------------
void red_green(void);
void red_yel(void);
void green_red(void);
void yel_red(void);
void disable_all_traffic_light(void);
//---------------------------------------------------------

//----MODE_2/3/4: CONFIG MODE---------------------------------------
void init_cfg_red(void);
void init_cfg_yel(void);
void init_cfg_gre(void);

void cfg_red_run(void);
void cfg_yel_run(void);
void cfg_gre_run(void);

void confirm_red_time(void);
void confirm_yel_time(void);
void confirm_gre_time(void);

void turn_all_red(void);
void turn_all_yel(void);
void turn_all_gre(void);
//-----------------------------------------------------------------


#endif /* INC_LAB_3_H_ */
