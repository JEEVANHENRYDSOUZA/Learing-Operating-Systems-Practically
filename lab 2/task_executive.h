#include <stdio.h>
#include <stdint.h>

#include "common.h"
#include "task_executive.h"

int32_t counter = 0;
int32_t previousCounter;

void TaskIdle(void *data){
}

void Task1(void *data){
  previousCounter = counter;
  counter = counter + 1;
  printf("Task1 is running, change counter from %ld to %ld\n",previousCounter,counter);
}

void Task2(void *data){
  previousCounter = counter;
  counter = counter - 1;
  printf("Task2 is running, change counter from %ld to %ld\n",previousCounter,counter);
}

void Task3(void *data){
  printf("Task3 is running\n");  
  
}

void Task4(void *data){
  TaskKill(1);
  TaskKill(2);
  TaskKill(4);

  printf("Task4 is running, killed task1, task2, and itself\n");
}

ParserReturnVal_t CmdTaskTest(int mode){
 
  if(mode != CMD_INTERACTIVE) return CmdReturnOk;

  
  TaskAdd(TaskIdle, NULL);
  TaskAdd(Task1, NULL);
  TaskAdd(Task2, NULL);
  TaskAdd(Task3, NULL);
  TaskAdd(Task4, NULL);
  TaskInit();


  
 for(int i = 0; i < 6; i++) {
    TaskSwitcher();
    }  
 return CmdReturnOk;
}

ADD_CMD("tasktest",CmdTaskTest,"the Task Executive");
