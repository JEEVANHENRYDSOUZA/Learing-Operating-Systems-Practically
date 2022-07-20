#include <stdio.h>
#include <stdint.h>
#include "common.h"
#include <task_state.h>
static int i = 0;

void TaskIdle(void *data)
{
	NULL;
}

void Task0(void *data)
{
	printf("Task0 is running, which serves as the idle task\n");
}

void Task1(void *data)
{
	static int state = 0;
	if (state == 0)
	{
		printf("Task1 is running, pended\n");
		TaskPending(1);
		state = 1;
	}
	else
	{
		printf("Task1 resumes\n");
		state = 0;
	}
}

void Task2(void *data)
{
	
	printf("Task2 is running, killed itself\n");
	TaskKill(2);
}

void Task3(void *data)
{
	static int count = 0;
	
	if (count <= 1)
	{
		count++;
		printf("Task3 is running\n");	
	}
	else if(count > 1)
	{
		printf("Task3 is running, reactivate Task2 and kill itself\n");
		TaskReady(2);
		TaskKill(3);
//		count = 0;
	}
		
}

void Fake_Interrupt (void *data)
{
	printf("Enter FakeInterrupt, putting Task1 to ready state\n");
	TaskReady(1);
}

ParserReturnVal_t CmdTaskTest(int mode)
{

	if(mode != CMD_INTERACTIVE) return CmdReturnOk;
	TaskInit();
//	TaskAdd(TaskIdle, NULL);
	TaskAdd(Task0, NULL);
	TaskAdd(Task1, NULL);
	TaskAdd(Task2, NULL);
	TaskAdd(Task3, NULL);
	TaskAdd(Fake_Interrupt, NULL);

	
	for(i = 0; i < 20; i++) 
	{
		TaskSwitcher();
	}
	return CmdReturnOk;
}
ADD_CMD("tasktest",CmdTaskTest," Test the Task Executive");
