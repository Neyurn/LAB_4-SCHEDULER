/*
 * scheduler.c
 *
 *  Created on: Nov 18, 2025
 *      Author: Khôi Nguyên
 */


#include "scheduler.h"

struct Node list[SCH_MAX_TASKS];
int32_t head = -1;
int32_t freeHead = 0;
enum ErrorCode Error_code_G = INIT;

void resetNode(int32_t index){
	list[index].data.pTask = NULL;
	list[index].data.Delay = 0;
	list[index].data.Period = 0;
	list[index].data.RunMe = 0;
	list[index].data.TaskID = 0;
}
void init_freelist(){
	for(int i=0; i< SCH_MAX_TASKS - 1; ++i){
		list[i].next = i+1;
	}
	list[SCH_MAX_TASKS-1].next = -1;
}
void List_init(){
	head = -1;
	freeHead = 0;
	init_freelist();
}
int32_t List_getfreeIndex(){
	if(freeHead == -1) return -1;

	int32_t freeIndex = freeHead;
	freeHead =  list[freeHead].next;

	return freeIndex;
}
void List_freeIndex(int32_t index){
	resetNode(index);
	list[index].next = freeHead;
	freeHead = index;
}
int8_t List_isempty(){
	return head == -1;
}
void List_insert(int32_t index){
	if(head == -1){
		if(list[index].data.Delay ==0){
			list[index].data.RunMe = 1;
		}
		head = index;
		list[index].next =  -1;
		return;
	}
	// find free index
	int32_t curr = head;
	int32_t pre  = -1;
	while(curr != -1){
		if(list[curr].data.Delay > list[index].data.Delay){ // them trc curr
			if(list[index].data.Delay == 0) list[index].data.RunMe =1;

			list[index].next = curr;
			if(pre == -1){
				head = index;
			}else{
				list[pre].next = index;
			}
			list[curr].data.Delay -= list[index].data.Delay;
			if(list[curr].data.Delay == 0) list[curr].data.RunMe = 1;
			return;
		}
		list[index].data.Delay -= list[curr].data.Delay;
		pre = curr;
		curr = list[curr].next;

	}

	//insert at tail == curr = -1
	if(list[index].data.Delay == 0 ) list[index].data.RunMe = 1;
	list[pre].next = index;
	list[index].next = -1;
}


void List_removeHead(){
	if(head == -1 ){
		Error_code_G = ERROR_SCH_EMPTY_LIST_CAN_NOT_REMOVED;
		return;
	}
	head = list[head].next;
}


//========================

void SCH_Init(void){
	List_init();
	Error_code_G = INIT;
}
uint32_t SCH_Add_Task(void (*pFunc)(),
						uint32_t DELAY,
						uint32_t PERIOD){
	int32_t freeIndex = List_getfreeIndex();
	if(freeIndex == -1){
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		return RETURN_ADD_ERROR;
	}
	list[freeIndex].data.pTask = pFunc;
	list[freeIndex].data.Delay = DELAY;
	list[freeIndex].data.Period = PERIOD; //ms to Tick
	list[freeIndex].data.RunMe = 0;
	list[freeIndex].data.TaskID = freeIndex;

	List_insert(freeIndex);
	return freeIndex; // Task ID
}
void SCH_Update(void){
	if(List_isempty()) return;
	if(list[head].data.Delay >0){
		--list[head].data.Delay;
	}
	if(list[head].data.Delay == 0) list[head].data.RunMe =1 ;
}
void SCH_Dispatch_Tasks(void){
	if(List_isempty()) return;

	int32_t curr = head;
	if(list[curr].data.RunMe == 1){
		//Run taks
		list[curr].data.RunMe = 0;
		list[curr].data.pTask();
		List_removeHead();


		if(list[curr].data.Period == 0){
			//ONE-SHOT
			List_freeIndex(curr);
		}else{
			//PERIODIC
			list[curr].data.Delay = list[curr].data.Period;
			List_insert(curr);
		}
	}

	__WFI();
}
uint8_t SCH_Delete_Task(uint32_t taskID){
	if(List_isempty()){
		Error_code_G = ERROR_SCH_EMPTY_LIST_CAN_NOT_DELETE;
		return RETURN_ERROR;
	}
	int32_t curr = head;
	int32_t pre = -1;
	while(curr!= -1){
		if(list[curr].data.TaskID == taskID){
			if(pre == -1){ // ID of Head
				if(list[curr].next != -1){
					list[list[curr].next].data.Delay += list[curr].data.Delay;
					if(list[list[curr].next].data.Delay != 0){
						list[list[curr].next].data.RunMe = 0;
					}
				}
				List_removeHead();
				List_freeIndex(curr);
			}
			else{
				if(list[curr].next != -1){
					list[list[curr].next].data.Delay += list[curr].data.Delay;
					if(list[list[curr].next].data.Delay != 0){
						list[list[curr].next].data.RunMe = 0;
					}
				}
				list[pre].next = list[curr].next;
				resetNode(curr);
				List_freeIndex(curr);
			}
			return 	RETURN_NORMAL;
		}
		pre = curr;
		curr = list[curr].next;
	}
	return RETURN_NORMAL;

}
void SCH_Go_To_Sleep(){
	//2.3.8
}
void SCH_Report_Status(){
	//2.3.9
}
