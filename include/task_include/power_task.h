#ifndef POWER_TASK_H
#define POWER_TASK_H

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t power_handler;

void power_task_function(void* pvParameters);

typedef struct {
  uint16_t power_status;
  uint16_t voltage_output;
  uint16_t current_output;
  int16_t temperature;
  uint16_t fan_1;
  uint16_t fan_2;
} PowerStat_t;

extern PowerStat_t SideCarPower_Stat[4];
#endif