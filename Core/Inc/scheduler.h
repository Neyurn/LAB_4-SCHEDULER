/*
 * scheduler.h
 *
 *  Created on: Nov 18, 2025
 *      Author: Khôi Nguyên
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


#define RETURN_ERROR 0
#define RETURN_NORMAL 1
#define RETURN_ADD_ERROR UINT32_MAX
#define NO_TASK_ID 0

#include "stdint.h" // thu san cho data 32bit xem tu record
#include "main.h"

typedef struct{
	void(*pTask)(void); // pointer den task
	uint32_t Delay;
	uint32_t Period;
	uint32_t RunMe;
	uint32_t TaskID; // index in task List
} sTask;
#define SCH_MAX_TASKS 5
//Use Linked List
struct Node{
	sTask data;
	int32_t next;
};

//For 2.3.9 Reporting errors
enum ErrorCode{
	INIT,
	ERROR_SCH_TOO_MANY_TASKS,
	ERROR_SCH_EMPTY_LIST_CAN_NOT_REMOVED,
	ERROR_SCH_EMPTY_LIST_CAN_NOT_DELETE
};


extern struct Node list[SCH_MAX_TASKS];
extern int32_t head;
extern int32_t freeHead;
extern enum ErrorCode Error_code_G;

//=========SET UP LIST =======
void resetNode(int32_t index);
void init_freelist();
void List_init();
int32_t List_getfreeIndex();
void List_freeIndex(int32_t index);
int8_t List_isempty();
void List_insert(int32_t index);
void List_removeHead();


//========================

void SCH_Init(void);
uint32_t SCH_Add_Task(void (*pFunc)(),
						uint32_t DELAY,
						uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t taskID);
void SCH_Go_To_Sleep();  //2.3.8
void SCH_Report_Status(); //2.3.9



#endif /* INC_SCHEDULER_H_ */
