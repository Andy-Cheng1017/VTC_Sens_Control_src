/* add user code begin Header */
/**
 **************************************************************************
 * @file     main.c
 * @brief    main program
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f421_wk_config.h"
#include "wk_adc.h"
#include "wk_crc.h"
#include "wk_exint.h"
#include "wk_i2c.h"
#include "wk_pwc.h"
#include "wk_tmr.h"
#include "wk_usart.h"
#include "wk_dma.h"
#include "wk_gpio.h"
#include "wk_system.h"
#include "FreeRTOS.h"
#include "task.h"
#include "pressure_task.h"
#include "pt100_task.h"
#include "RS485_task.h"
#include "temp_hum_task.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE 128

#define PT100_TASK_PRIO 3
#define PT100_STK_SIZE 256

#define RS485_TASK_PRIO 3
#define RS485_STK_SIZE 512

#define PRESSURE_TASK_PRIO 3
#define PRESSURE_STK_SIZE 256

#define TEMP_HUM_TASK_PRIO 2
#define TEMP_HUM_STK_SIZE 256

#define SET_BIT_TO(var, bit, value) ((var) = (value) ? ((var) & ~(1 << (bit))) : ((var) | (1 << (bit))))

TaskHandle_t StartTask_Handler;
void start_task(void* pvParameters);

void EXINT3_2_IRQHandler(void) {
  if (exint_interrupt_flag_get(EXINT_LINE_3) != RESET) {
    exint_flag_clear(EXINT_LINE_3);
    SET_BIT_TO(SensStat.leak_sensor, 1, gpio_input_data_bit_read(GPIOB, GPIO_PINS_3));
  }
}

void EXINT15_4_IRQHandler(void) {
  if (exint_interrupt_flag_get(EXINT_LINE_7) != RESET) {
    exint_flag_clear(EXINT_LINE_7);
    SET_BIT_TO(SensStat.leak_sensor, 2, gpio_input_data_bit_read(GPIOB, GPIO_PINS_7));
  }
  if (exint_interrupt_flag_get(EXINT_LINE_8) != RESET) {
    exint_flag_clear(EXINT_LINE_8);
    SET_BIT_TO(SensStat.leak_sensor, 3, gpio_input_data_bit_read(GPIOB, GPIO_PINS_8));
  }
  if (exint_interrupt_flag_get(EXINT_LINE_15) != RESET) {
    exint_flag_clear(EXINT_LINE_15);
    SET_BIT_TO(SensStat.leak_sensor, 0, gpio_input_data_bit_read(GPIOA, GPIO_PINS_15));
  }
}

int main(void) {
  /* add user code begin 1 */

  /* add user code end 1 */

  /* system clock config. */
  wk_system_clock_config();

  /* config periph clock. */
  wk_periph_clock_config();

  /* init pwc function. */
  wk_pwc_init();

  /* nvic config. */
  wk_nvic_config();

  /* timebase config. */
  wk_timebase_init();

  /* init dma1 channel1 */
  wk_dma1_channel1_init();
  /* config dma channel transfer parameter */
  /* user need to modify define values DMAx_CHANNELy_XXX_BASE_ADDR and DMAx_CHANNELy_BUFFER_SIZE in at32xxx_wk_config.h */
  wk_dma_channel_config(DMA1_CHANNEL1, (uint32_t)&ADC1->odt, DMA1_CHANNEL1_MEMORY_BASE_ADDR, DMA1_CHANNEL1_BUFFER_SIZE);
  dma_channel_enable(DMA1_CHANNEL1, TRUE);

  /* init usart1 function. */
  wk_usart1_init();

  /* init usart2 function. */
  wk_usart2_init();

  /* init i2c2 function. */
  wk_i2c2_init();

  /* init crc function. */
  wk_crc_init();

  /* init adc1 function. */
  wk_adc1_init();

  /* init exint function. */
  wk_exint_config();

  /* init gpio function. */
  wk_gpio_config();

  /* init tmr3 function. */
  wk_tmr3_init();

  /* init tmr15 function. */
  wk_tmr15_init();

  /* add user code begin 2 */
  exint_interrupt_enable(EXINT_LINE_3, TRUE);
  exint_software_interrupt_event_generate(EXINT_LINE_3);
  wk_delay_ms(1);
  exint_interrupt_enable(EXINT_LINE_7, TRUE);
  exint_software_interrupt_event_generate(EXINT_LINE_7);
  wk_delay_ms(1);
  exint_interrupt_enable(EXINT_LINE_8, TRUE);
  exint_software_interrupt_event_generate(EXINT_LINE_8);
  wk_delay_ms(1);
  exint_interrupt_enable(EXINT_LINE_15, TRUE);
  exint_software_interrupt_event_generate(EXINT_LINE_15);
  wk_delay_ms(1);

  /* add user code end 2 */

  xTaskCreate((TaskFunction_t)start_task, (const char*)"start_task", (uint16_t)START_STK_SIZE, (void*)NULL, (UBaseType_t)START_TASK_PRIO,
              (TaskHandle_t*)&StartTask_Handler);
  vTaskStartScheduler();
}

void start_task(void* pvParameters) {
  vTaskDelay(100);
  xTaskCreate((TaskFunction_t)RS485_task_function, (const char*)"RS485_task", (uint16_t)RS485_STK_SIZE, (void*)NULL, (UBaseType_t)RS485_TASK_PRIO,
              (TaskHandle_t*)&RS485Task_Handler);
  vTaskDelay(100);
  xTaskCreate((TaskFunction_t)pt100_task_function, (const char*)"pt100_task", (uint16_t)PT100_STK_SIZE, (void*)NULL, (UBaseType_t)PT100_TASK_PRIO,
              (TaskHandle_t*)&pt100_handler);
  vTaskDelay(100);
  xTaskCreate((TaskFunction_t)pressure_task_function, (const char*)"pressure_task", (uint16_t)PRESSURE_STK_SIZE, (void*)NULL,
              (UBaseType_t)PRESSURE_TASK_PRIO, (TaskHandle_t*)&pressure_handler);
  vTaskDelay(100);
  xTaskCreate((TaskFunction_t)temp_hum_task_function, (const char*)"Temp_Hum_task", (uint16_t)TEMP_HUM_STK_SIZE, (void*)NULL,
              (UBaseType_t)TEMP_HUM_TASK_PRIO, (TaskHandle_t*)&temp_hum_handler);
  vTaskDelay(100);
  vTaskDelete(StartTask_Handler);
}
