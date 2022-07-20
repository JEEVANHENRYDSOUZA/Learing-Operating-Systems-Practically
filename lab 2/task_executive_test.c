#include <stdio.h>
#include <stdint.h>
#include "common.h"
#include <task_executive.h>
#define MAX_TASKS 10

typedef struct Task_s {
void (*f)(void *data); /* Task function */
void *data; /* Private data pointer for this task */
} Task_t;

Task_t tasks[MAX_TASKS];  // intiialize tasks array 
int32_t currentTask ;

void TaskInit(void){
  tasks[currentTask].f(tasks[currentTask].data);
}



int32_t TaskAdd(void (*f)(void *data), void *data) {
  /* Try to find an empty slot */
  for(int32_t i=0; i<MAX_TASKS; i++) {
    if(tasks[i].f == NULL) {
	    tasks[i].f = f;
	    tasks[i].data = data;
	    return i;
      }
  }
  /* No slots available, return -1 */
  return -1;
}


static int32_t TaskNext(void)
{
  int32_t i;
  uint32_t count=0;
  i = currentTask;
  do {
    i = (i + 1) % MAX_TASKS;
    count++;
  } while((tasks[i].f == NULL) && (count <= MAX_TASKS));
  return (count <= MAX_TASKS) ? i : -1;
}


int32_t TaskKill(int32_t id) {
  tasks[id].f = NULL;
  tasks[id].data = NULL;
  return id;
}



int32_t TaskSwitcher(void) {
  currentTask = TaskNext();
  if(currentTask < 0) {
    return -1;
  }
  if(currentTask > MAX_TASKS)
  {
    currentTask = 0;
  }
  tasks[currentTask].f(tasks[currentTask].data);
  return currentTask;
}



int32_t TaskCurrent(void) {
  
  return currentTask;
}

