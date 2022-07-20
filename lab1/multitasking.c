#include <stdio.h>
#include <stdint.h>
#include "common.h"
/* Global counter for printing messages */
static uint32_t Counter;

void TaskCounter(void *data)
{
if(Counter) {
printf("The counter is %u\n",(unsigned)Counter);
Counter--;
}
}



/* Monitor command to set the counter variable */
ParserReturnVal_t CmdCount(int mode)
{
uint32_t count;
if(mode != CMD_INTERACTIVE) return CmdReturnOk;
count = 0;
fetch_uint32_arg(&count);
Counter += count;
return CmdReturnOk;
}
ADD_CMD("count", CmdCount,
"<n> Add <n> to the message print count");




ADD_TASK(TaskCounter, /* This is the name of the function for the task */
NULL, /* This is the initialization function */
NULL, /* This pointer is passed as 'data' to the functions */
500, /* This is the number of milliseconds between calls */
"This is the help text for the counter task");
