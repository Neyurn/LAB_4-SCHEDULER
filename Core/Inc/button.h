/*
 * button.h
 *
 *  Created on: Nov 18, 2025
 *      Author: Khôi Nguyên
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "global.h"

#define NORMAL_STATE 1
#define PRESSED_STATE 0

struct ButtonStruct {
	uint8_t 		keyBuffer[4];
	uint16_t 		timeOutForPressed;
	uint8_t 		isPressed;
	uint8_t 		isLongPressed;
	GPIO_TypeDef 	*PORT;
	uint16_t 		PIN;
};

extern struct ButtonStruct button0;
extern struct ButtonStruct button1;
extern struct ButtonStruct button2;

void getKeyInput(struct ButtonStruct* button);
uint8_t isButtonPressed(struct ButtonStruct *button);
uint8_t isButtonLongPressed(struct ButtonStruct *button);
void resetButton(struct ButtonStruct *button);


#endif /* INC_BUTTON_H_ */
