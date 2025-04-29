#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "power_task.h"

TaskHandle_t power_handler;

PowerStat_t SideCarPower_Stat[4] = {0};

void power_task_function(void* pvParameters) {

  while (1) {
    vTaskDelay(1000);
  }
  vTaskDelete(NULL);
}