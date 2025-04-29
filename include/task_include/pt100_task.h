#ifndef PT100_TASK_H
#define PT100_TASK_H

#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t pt100_handler;

typedef struct {
  int32_t pt100_raw_l_val[4];
  int32_t pt100_raw_h_val[4];
  int32_t pt100_ideal_l_val;
  int32_t pt100_ideal_h_val;
} Pt100TwoCal_t;

extern Pt100TwoCal_t SensPt100TwoCal;

void pt100_task_function(void* pvParameters);

#endif // PT100_TASK_H