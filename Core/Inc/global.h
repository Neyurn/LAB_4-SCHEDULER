/*
 * global.h
 *
 *  Created on: Nov 19, 2025
 *      Author: Khôi Nguyên
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

//#define STATUS_LED_TIMER	0
//#define NORMAL_TIMER 		1
//#define CLOCK_TIMER		2
//#define CLOCK_COUNTER		3
//#define CONFIG_TIMER		4
//#define DISPLAY_TIMER		5

#define RED_TIME        	7
#define YEL_TIME 			3
#define GRE_TIME 			4

#define CONFIG_TIME			50


//LED_7_SEGMENT
enum traffic_light_state{
	INIT_TFL,

	//Auto mode
	AUTO_RED_GRE,
	AUTO_RED_YEL,
	AUTO_GRE_RED,
	AUTO_YEL_RED,

	// Manual mode
	MAN_RED_GRE,
	MAN_RED_YEL,
	MAN_GRE_RED,
	MAN_YEL_RED,

	// Config mode
	CFG_RED,
	CFG_YEL,
	CFG_GRE,

	//Clock for road
	SEG0, SEG1,   // doc
	SEG2, SEG3    // ngang
};

extern uint8_t tfl_status; // traffic light status

extern uint16_t X_clock;
extern uint16_t Y_clock;

extern uint8_t red_time;
extern uint8_t yel_time;
extern uint8_t gre_time;

// TIMER
#define TIMER_READ_BTN 0
#define TIME_READ_BTN 20 // ms

// LED CONTROL
#define LED_ON 0
#define LED_OFF 1

// BUTTON
#define NORMAL_STATE 1
#define PRESSED_STATE 0
#define TIME_OUT_FOR_LONG_PRESSED 500 // ms

#endif /* INC_GLOBAL_H_ */
