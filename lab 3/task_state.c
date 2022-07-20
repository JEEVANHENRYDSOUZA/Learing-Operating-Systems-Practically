
#include <stdio.h>
#include <stdint.h>
#include "common.h"
#include "main.h"
#define MAX_TASKS 10
#include <task_state.h>
int32_t i;

typedef enum {
	TASK_READY = 0,
	TASK_PENDING,
	TASK_RUNNING,
	TASK_INACTIVE,
	TASK_INTERRUPTED,
	TASK_STATE_MAX
	} TaskState_e;

typedef struct Task_s {
	void (*f)(void *data); 		
	void *data; 			
	TaskState_e state; 		
	} Task_t;


Task_t tasks[MAX_TASKS];
int32_t currentTask;

void TaskInit(void)
{
	currentTask = MAX_TASKS - 1;
}

int32_t TaskAdd(void (*f)(void *data), void *data)
{

	for(i=0; i<MAX_TASKS; i++) 
	{
		if(tasks[i].f == NULL) 
		{
		tasks[i].f = f;
		tasks[i].data = data;

		return i;
		}
	}
	
	return -1;
}

int32_t TaskKill(int32_t id)
{
	if((tasks[id].state == TASK_READY) || (tasks[id].state == TASK_RUNNING))
		{
			tasks[id].state = TASK_INACTIVE;
			return 0;
		}
	else
	return -1;
}

int32_t TaskPending(int32_t id)
{
	if((tasks[id].state == TASK_RUNNING))
		{
		tasks[id].state = TASK_PENDING;
		return 0;
		}
	else
	return -1;
}

int32_t TaskReady(int32_t id)
{
	if((tasks[id].state == TASK_PENDING) || (tasks[id].state == TASK_RUNNING) || (tasks[id].state == TASK_INACTIVE))
		{
		tasks[id].state = TASK_READY;
		return 0;
		}
	else
	return -1;
}

int32_t TaskCurrent(void)
{
	return currentTask;
}


static int32_t TaskNext(void)
{
	uint32_t count=0;
	i = currentTask;
	do {
		i = (i + 1) % MAX_TASKS;
		count++;
	} while(((tasks[i].f == NULL) || (tasks[i].state != TASK_READY)) && (count <= MAX_TASKS));
	return (count <= MAX_TASKS) ? i : -1;
}

int32_t TaskSwitcher(void)
{
	
	currentTask = TaskNext();
	if(currentTask < 0) {
	return -1;
	}
	tasks[currentTask].f(tasks[currentTask].data);
	return 0;
}
