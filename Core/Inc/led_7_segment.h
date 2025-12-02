/*
 * led_7_segment.h
 *
 *  Created on: Nov 28, 2025
 *      Author: Khôi Nguyên
 */

#ifndef INC_LED_7_SEGMENT_H_
#define INC_LED_7_SEGMENT_H_

#include "main.h"
#include "global.h"

extern uint8_t clock_status;

void update_clock_buffer();
void display_clock();
void display_X_num(uint8_t num); // duong ngang
void display_Y_num(uint8_t num); // duong doc

void disable_all();
void enable_num(uint8_t idx);



#endif /* INC_LED_7_SEGMENT_H_ */
