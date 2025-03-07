#ifndef RS485_TASK_H
#define RS485_TASK_H

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t RS485Task_Handler;

void RS485_task_function(void * parameter);

#endif