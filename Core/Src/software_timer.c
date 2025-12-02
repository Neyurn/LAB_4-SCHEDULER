/*
 * software_timer.c
 *
 *  Created on: Oct 5, 2025
 *      Author: Khôi Nguyên
 */


#include "software_timer.h"


#define MAX_COUNTER 10 //6
struct TimerStruct timer[10];

//Set the counter for software timer
void setTimer(int idx, int counter){
	timer[idx].counter = counter/10;
	timer[idx].flag = 0;
}

//Check if timer is expired
int isFlag( int idx){
	if(timer[idx].flag==1){
		//timer[idx].flag = 0;  // comment if many file
		return 1;
	}
	return 0;
}

//Function to be invoked in Timer_ISR
void timerRun(){
	for(int i=0; i <10; i++){
		if (timer[i].counter > 0) {
			--timer[i].counter;
			if(timer[i].counter <= 0) timer[i].flag = 1;
		}
	}
}

int ms_to_Tich(int time_ms){
	return time_ms/10;
}
