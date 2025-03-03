#ifndef PRESSURE_TASK_H
#define PRESSURE_TASK_H
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"

#define ADC1_CHANNEL_NUM 3
#define ADC1_SAMPLE_NUM 32
#define SMP_NUM_PWR (__builtin_ctz(ADC1_SAMPLE_NUM))

_Static_assert((ADC1_SAMPLE_NUM & (ADC1_SAMPLE_NUM - 1)) == 0, "ADC1_SAMPLE_NUM must be a power of 2");

extern uint16_t adc1_ordinary_valuetab[ADC1_SAMPLE_NUM][ADC1_CHANNEL_NUM];
extern TaskHandle_t pressure_handler;

typedef struct {
  int16_t press_1_val;
  int16_t press_2_val;
  uint8_t leak_sensor;
} SensStat_t;

extern SensStat_t SensStat;

typedef struct {
  int16_t press_1_raw_l_val;
  int16_t press_2_raw_l_val;
  int16_t press_1_raw_h_val;
  int16_t press_2_raw_h_val;
  int16_t press_ideal_l_val;
  int16_t press_ideal_h_val;
} PressTwoCal_t;

extern PressTwoCal_t PressTwoCal;

void pressure_task_function(void* pvParameters);

#endif  // PRESSURE_TASK_H