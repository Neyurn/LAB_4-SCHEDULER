/*
 * software_timer.h
 *
 *  Created on: Nov 4, 2025
 *      Author: Khôi Nguyên
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

struct TimerStruct{
	int counter;
	int flag;
};

extern struct TimerStruct timer[10];

void setTimer(int idx, int counter);
int isFlag(int idx);

void timerRun();
int ms_to_Tich(int time_ms);

#endif /* INC_SOFTWARE_TIMER_H_ */
