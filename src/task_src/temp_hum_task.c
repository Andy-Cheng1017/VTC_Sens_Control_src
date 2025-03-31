/**
 * @file temp_hum_task.c
 * @brief Temperature and humidity monitoring task implementation
 */
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "RS485.h"
#include "temp_hum_task.h"

#define TEMP_HUM_TASK_PERIOD 1000

#define TEMP_HUM_ADDR 0x01
#define TEMP_HUM_REG_START 0x01
#define TEMP_HUM_TOTAL_REG_NUM 2

TaskHandle_t temp_hum_handler;

Rs485_t RsTempHum = {
    .UART = USART1,
    .Mode = MASTER,
    .BaudRate = BR_9600,
    .DataBit = USART_DATA_8BITS,
    .StopBit = USART_STOP_1_BIT,
    .ip_addr = TEMP_HUM_ADDR,
    .root = true,
    .tx_Func = READ_INPUT_REGISTERS,
    .reg_hdle_num = TEMP_HUM_TOTAL_REG_NUM,
};

void USART1_IRQHandler(void) {
  if (usart_interrupt_flag_get(RsTempHum.UART, USART_RDBF_FLAG) != RESET) {
    usart_flag_clear(RsTempHum.UART, USART_RDBF_FLAG);
    RS485_Rx_Data_ISR(&RsTempHum);

  } else if (usart_interrupt_flag_get(RsTempHum.UART, USART_IDLEF_FLAG) != RESET) {
    usart_flag_clear(RsTempHum.UART, USART_IDLEF_FLAG);
    RS485_Rx_Cplt_ISR(&RsTempHum);

  } else if (usart_interrupt_flag_get(RsTempHum.UART, USART_TDBE_FLAG) != RESET) {
    usart_flag_clear(RsTempHum.UART, USART_TDBE_FLAG);
    usart_interrupt_enable(RsTempHum.UART, USART_TDBE_INT, FALSE);
    RS485_Tx_Data_ISR(&RsTempHum);
  }
}

void temp_hum_task_function(void *pvParameters) {
  RsInit(&RsTempHum);

  TickType_t xLastWakeTime = xTaskGetTickCount();
  RsError_t ret;
  while (1) {
    vTaskDelayUntil(&xLastWakeTime, TEMP_HUM_TASK_PERIOD);

    RsTempHum.reg_hdle_stat = TEMP_HUM_REG_START;

    ret = RS485WriteHandler(&RsTempHum, NULL, NULL);
    if (ret) {
      continue;
    }

    ret = RS485Write(&RsTempHum);
    if (ret) {
      continue;
    }

    TickType_t start_time = xTaskGetTickCount();

    while (1) {
      if (RsChkAvailable(&RsTempHum)) {
        ret = RS485Read(&RsTempHum);

        if (ret == UNPKG_FINISH) {
          break;
        } else if (ret != RS485_OK) {
          break;
        } else {
        }
        RsTempHum.reg_hdle_stat = 0X57;

        ret = RS485ReadHandler(&RsTempHum);

        if (ret != RS485_OK) {
        }
        break;
      }

      if ((xTaskGetTickCount() - start_time) > TEMP_HUM_TASK_PERIOD) {
        break;
      }

      vTaskDelay(25);
    }
  }
}