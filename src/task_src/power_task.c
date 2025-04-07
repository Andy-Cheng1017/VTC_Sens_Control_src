#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "power_task.h"

TaskHandle_t power_handler;

PowerStat_t Power_1_Stat = {0};
PowerStat_t Power_2_Stat = {0};
PowerStat_t Power_3_Stat = {0};
PowerStat_t Power_4_Stat = {0};

void power_task_function(void* pvParameters) {

  while (1) {
    vTaskDelay(1000);
  }
  vTaskDelete(NULL);
}