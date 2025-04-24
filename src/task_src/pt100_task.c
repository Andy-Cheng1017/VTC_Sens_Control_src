#include <stdio.h>
#include <string.h>
#include "pt100_task.h"
#include "pt100.h"
#include "pressure_task.h"
#include "MCP342x_wrap.h"
#include "Two_Pt_Cal.h"

#define PT100_TASK_PERIOD 200

MCP342x_error_t err;

TaskHandle_t pt100_handler;

Pt100I2cParam_t Pt100I2cParam = {
    .i2c_handle =
        {
            .i2cx = I2C2,
            .timeout = 0xFFFFFFFF,
        },
    .mcp_i2c_addr = 0xD0,
    .adc_gain = 3,
};

Pt100TwoCal_t Pt100TwoCal = {
    .pt100_1_raw_l_val = 25684,
    .pt100_2_raw_l_val = 25684,
    .pt100_3_raw_l_val = 25684,
    .pt100_4_raw_l_val = 25684,
    .pt100_1_raw_h_val = 90770,
    .pt100_2_raw_h_val = 90770,
    .pt100_3_raw_h_val = 90770,
    .pt100_4_raw_h_val = 90770,
    .pt100_ideal_l_val = 25684,  // 110ohm
    .pt100_ideal_h_val = 90770,  // 135ohm
};

CalParam_t PtCal[4] = {
    [0] =
        {
            .offset = 0.0f,
            .slope = 1.0f,
            .raw_l = &Pt100TwoCal.pt100_1_raw_l_val,
            .raw_h = &Pt100TwoCal.pt100_1_raw_h_val,
            .ideal_l = &Pt100TwoCal.pt100_ideal_l_val,
            .ideal_h = &Pt100TwoCal.pt100_ideal_h_val,
            .data_type = DATA_TYPE_INT32,
        },
    [1] =
        {
            .offset = 0.0f,
            .slope = 1.0f,
            .raw_l = &Pt100TwoCal.pt100_2_raw_l_val,
            .raw_h = &Pt100TwoCal.pt100_2_raw_h_val,
            .ideal_l = &Pt100TwoCal.pt100_ideal_l_val,
            .ideal_h = &Pt100TwoCal.pt100_ideal_h_val,
            .data_type = DATA_TYPE_INT32,
        },
    [2] =
        {
            .offset = 0.0f,
            .slope = 1.0f,
            .raw_l = &Pt100TwoCal.pt100_3_raw_l_val,
            .raw_h = &Pt100TwoCal.pt100_3_raw_h_val,
            .ideal_l = &Pt100TwoCal.pt100_ideal_l_val,
            .ideal_h = &Pt100TwoCal.pt100_ideal_h_val,
            .data_type = DATA_TYPE_INT32,
        },
    [3] =
        {
            .offset = 0.0f,
            .slope = 1.0f,
            .raw_l = &Pt100TwoCal.pt100_4_raw_l_val,
            .raw_h = &Pt100TwoCal.pt100_4_raw_h_val,
            .ideal_l = &Pt100TwoCal.pt100_ideal_l_val,
            .ideal_h = &Pt100TwoCal.pt100_ideal_h_val,
            .data_type = DATA_TYPE_INT32,
        },
};

uint16_t MCP_Remap(int i) {
  if (i == 0) {
    i = 2;
  } else if (i == 1) {
    i = 3;
  } else if (i == 2) {
    i = 0;
  } else if (i == 3) {
    i = 1;
  }
  return i;
}

void pt100_task_function(void* pvParameters) {
  for (int i = 0; i < 4; i++) {
    Cal_CalcParams(&PtCal[i]);
  }

  PT100_Init(&Pt100I2cParam);

  TickType_t xLastWakeTime = xTaskGetTickCount();

  while (1) {
    vTaskDelayUntil(&xLastWakeTime, PT100_TASK_PERIOD);

    static int32_t raw_val = 0;
    for (int i = 0; i < 4; i++) {
      if (SensCardCtrl.pt100_enable & (1 << i)) {
        err = PT100_MCP_ReadAndCalcTemp(&Pt100I2cParam, MCP_Remap(i), &raw_val);
        if (err == errorNone) {
          SensCardStat.pt100_temp_m[i] = Cal_Apply(&PtCal[i], raw_val);
          // log_i("pt100_%d_temp_m: %d", i + 1, SensCardStat.pt100_temp_m[i]);
        } else {
          // log_e("MCP342x_convertAndRead error: %d", err);
        }
      }
    }
  }
  vTaskDelete(NULL);
}
