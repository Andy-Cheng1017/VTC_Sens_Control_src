#include <stdio.h>
#include <string.h>
#include "pressure_task.h"
#include "SensConvVal.h"
#include "Two_Pt_Cal.h"
#include "FG_RPM.h"

#define PRESSURE_TASK_PERIOD 500

SensCardStat_t SensCardStat = {0};
SensCardCtrl_t SensCardCtrl = {
    .pt100_enable = 0b0001,
};

uint16_t adc1_ordinary_valuetab[ADC1_SAMPLE_COUNT][ADC1_CHANNEL_COUNT] = {0};

TaskHandle_t pressure_handler;

SensPressTwoCal_t SensPressTwoCal = {
    .press_raw_l_val =
        {
            [0] = 0,
            [1] = 0,
        },
    .press_raw_h_val =
        {
            [0] = 2000,
            [1] = 2000,
        },
    .press_ideal_l_val = 0,     // 4ma
    .press_ideal_h_val = 2000,  // 7.2ma
};

CalParam_t PressCal[2] = {
    {
        .offset = 0.0f,
        .slope = 1.0f,
        .raw_l = &SensPressTwoCal.press_raw_l_val[0],
        .raw_h = &SensPressTwoCal.press_raw_h_val[0],
        .ideal_l = &SensPressTwoCal.press_ideal_l_val,
        .ideal_h = &SensPressTwoCal.press_ideal_h_val,
        .data_type = DATA_TYPE_INT16,
    },
    {
        .offset = 0.0f,
        .slope = 1.0f,
        .raw_l = &SensPressTwoCal.press_raw_l_val[1],
        .raw_h = &SensPressTwoCal.press_raw_h_val[1],
        .ideal_l = &SensPressTwoCal.press_ideal_l_val,
        .ideal_h = &SensPressTwoCal.press_ideal_h_val,
        .data_type = DATA_TYPE_INT16,
    },
};

ErrConv_t err_conv;
SensConvVal_t PressConv = {
    .volt_min = 0.6f,
    .volt_max = 3.0f,
    .sens_min = 0.0f,
    .sens_max = 10000.0f,
    .adc_res = 4095,
    .adc_ref = 3.3f,
};

void pressure_task_function(void* pvParameters) {
  int32_t raw_val = 0;

  Conv_Init(&PressConv);

  if (Cal_CalcParams(&PressCal[0])) {
    // log_e("PressCal_1 CalcParams failed");
  }
  if (Cal_CalcParams(&PressCal[1])) {
    // log_e("PressCal_2 CalcParams failed");
  }

  vTaskDelay(5);

  TickType_t xLastWakeTime = xTaskGetTickCount();

  while (1) {
    vTaskDelayUntil(&xLastWakeTime, PRESSURE_TASK_PERIOD);

    uint32_t adc_sum_val[ADC1_CHANNEL_COUNT] = {0};
    for (int i = 0; i < ADC1_CHANNEL_COUNT; i++) {
      for (int j = 0; j < ADC1_SAMPLE_COUNT; j++) {
        adc_sum_val[i] += adc1_ordinary_valuetab[j][i];
      }
    }

    for (int i = 0; i < 2; i++) {
      err_conv = Conv_GetVal_Volt(&PressConv,
                                  (((float)(adc_sum_val[i] >> SMP_CNT_PWR)) / (adc_sum_val[ADC1_CHANNEL_COUNT - 1] >> SMP_CNT_PWR)) * 1.2f, &raw_val);
      SensCardStat.press_val_kpa[i] = (int16_t)Cal_Apply(&PressCal[i], raw_val);
    }
  }

  vTaskDelete(NULL);
}
