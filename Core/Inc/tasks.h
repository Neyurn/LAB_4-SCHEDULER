/*
 * tasks.h
 *
 *  Created on: Nov 19, 2025
 *      Author: Khôi Nguyên
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

#include "button.h"
#include "main.h"
#include "global.h"
#include "led_7_segment.h"
#include "lab_3.h"

void led_init(void);
void blinky_led(void);
void get_button_input(void);
void control_3led(void);
void run_lab_3(void);


#endif /* INC_TASKS_H_ */
