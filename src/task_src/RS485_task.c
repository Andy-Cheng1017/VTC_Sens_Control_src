#include "RS485_task.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "RS485.h"
#include "RS485_Region_handler.h"
#include "task.h"

#define SINGLE_DATA_MAX_SIZE 128

TaskHandle_t RS485Task_Handler;

DECLARE_RS485_BUFFERS(RsSens, SINGLE_DATA_MAX_SIZE);

Rs485_t RsSens = {
    .UART = USART2,
    .Mode = SLAVE,
    .BaudRate = BR_115200,
    .DataBit = USART_DATA_8BITS,
    .StopBit = USART_STOP_1_BIT,
    .ip_addr = SENS_RS485_ADDR,
    .root = true,

    RS485_BUFFERS_INIT(RsSens, SINGLE_DATA_MAX_SIZE),
};

void USART2_IRQHandler(void) {
  if (usart_interrupt_flag_get(RsSens.UART, USART_RDBF_FLAG) != RESET) {
    usart_flag_clear(RsSens.UART, USART_RDBF_FLAG);
    RS485_Rx_Data_ISR(&RsSens);

  } else if (usart_interrupt_flag_get(RsSens.UART, USART_IDLEF_FLAG) != RESET) {
    usart_flag_clear(RsSens.UART, USART_IDLEF_FLAG);
    RS485_Rx_Cplt_ISR(&RsSens);

  } else if (usart_interrupt_flag_get(RsSens.UART, USART_TDBE_FLAG) != RESET) {
    usart_flag_clear(RsSens.UART, USART_TDBE_FLAG);
    usart_interrupt_enable(RsSens.UART, USART_TDBE_INT, FALSE);
    RS485_Tx_Data_ISR(&RsSens);
  }
}

void RS485_task_function(void* parameter) {
  RsInit(&RsSens);
  RsError_t err;

  while (1) {
    if (RsChkAvailable(&RsSens)) {
      err = RS485Read(&RsSens);

      if (err == UNPKG_FINISH) {
        continue;
      } else if (err != RS485_OK) {
        continue;
      }
      err = RS485ReadHandler(&RsSens);

      if (err != RS485_OK) {
        continue;
      }

      err = RS485Write(&RsSens);

      if (err != RS485_OK) {
        continue;
      }
    }

    vTaskDelay(25);
  }
  vTaskDelete(NULL);
}