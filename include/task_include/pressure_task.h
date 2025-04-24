#ifndef PRESSURE_TASK_H
#define PRESSURE_TASK_H
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"

#define ADC1_CHANNEL_COUNT 3
#define ADC1_SAMPLE_COUNT 32
#define SMP_CNT_PWR (__builtin_ctz(ADC1_SAMPLE_COUNT))

_Static_assert((ADC1_SAMPLE_COUNT & (ADC1_SAMPLE_COUNT - 1)) == 0, "ADC1_SAMPLE_COUNT must be a power of 2");

extern uint16_t adc1_ordinary_valuetab[ADC1_SAMPLE_COUNT][ADC1_CHANNEL_COUNT];
extern TaskHandle_t pressure_handler;

typedef struct {
  int32_t pt100_temp_m[4];
  int16_t press_1_val_kpa;
  int16_t press_2_val_kpa;
  uint8_t leak_sensor;
  int16_t temperature;
  int16_t humidity;
} SensCardStat_t;

extern SensCardStat_t SensCardStat;

typedef struct {
  int16_t press_1_raw_l_val;
  int16_t press_2_raw_l_val;
  int16_t press_1_raw_h_val;
  int16_t press_2_raw_h_val;
  int16_t press_ideal_l_val;
  int16_t press_ideal_h_val;
} PressTwoCal_t;

extern PressTwoCal_t PressTwoCal;

typedef struct {
  uint16_t pressure_pump;
  uint8_t pt100_enable;
}SensCardCtrl_t;

extern SensCardCtrl_t SensCardCtrl;

void pressure_task_function(void* pvParameters);

#endif  // PRESSURE_TASK_H