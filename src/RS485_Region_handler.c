#include "RS485_Region_handler.h"
#include "pressure_task.h"
#include "pt100_task.h"

typedef enum {
  SIDECAR_PT100_1_TEMPERATURE = SENS_CARD_DATAREAD_REG_START,
  SIDECAR_PT100_2_TEMPERATURE,
  SIDECAR_PT100_3_TEMPERATURE,
  SIDECAR_PT100_4_TEMPERATURE,
  SIDECAR_PRESSURE_1_VALUE,
  SIDECAR_PRESSURE_2_VALUE,
  SIDECAR_LEAK_SENSOR,
  SIDECAR_TEMPERATURE,
  SIDECAR_HUMIDITY,
  SIDECAR_RESERVED_1,
  SIDECAR_RESERVED_2,
  SIDECAR_RESERVED_3,
  SIDECAR_RESERVED_4,
  SIDECAR_RESERVED_5,
  SIDECAR_RESERVED_6,
  SIDECAR_RESERVED_7,
} SideCarSensReadCase_t;

typedef enum {
  SIDECAR_PRESSURE_PUMP = SENS_CARD_DEVCTRL_REG_START,
  SIDECAR_RESERVED_CTRL_1,
  SIDECAR_RESERVED_CTRL_2,
  SIDECAR_RESERVED_CTRL_3,
  SIDECAR_RESERVED_CTRL_4,
  SIDECAR_RESERVED_CTRL_5,
  SIDECAR_RESERVED_CTRL_6,
  SIDECAR_RESERVED_CTRL_7,
  SIDECAR_RESERVED_CTRL_8,
  SIDECAR_RESERVED_CTRL_9,
  SIDECAR_RESERVED_CTRL_10,
  SIDECAR_RESERVED_CTRL_11,
  SIDECAR_RESERVED_CTRL_12,
  SIDECAR_RESERVED_CTRL_13,
  SIDECAR_RESERVED_CTRL_14,
  SIDECAR_RESERVED_CTRL_15,
} SideCarDevCtrlCase_t;

uint32_t SideCar_Sens_DataRead_Handler(RsFunc_t func, uint16_t addr, uint16_t data, uint8_t len, bool root) {
  if (func == READ_HOLDING_REGISTERS) {
    switch (addr) {
      case SIDECAR_PT100_1_TEMPERATURE:
        return (Pt100Stat.pt100_1_temp_m / 100) & 0xFFFF;
      case SIDECAR_PT100_2_TEMPERATURE:
        return (Pt100Stat.pt100_2_temp_m / 100) & 0xFFFF;
      case SIDECAR_PT100_3_TEMPERATURE:
        return (Pt100Stat.pt100_3_temp_m / 100) & 0xFFFF;
      case SIDECAR_PT100_4_TEMPERATURE:
        return (Pt100Stat.pt100_4_temp_m / 100) & 0xFFFF;
      case SIDECAR_PRESSURE_1_VALUE:
        return (SensCardStat.press_1_val_kpa) & 0xFFFF;
      case SIDECAR_PRESSURE_2_VALUE:
        return (SensCardStat.press_2_val_kpa) & 0xFFFF;
      case SIDECAR_LEAK_SENSOR:
        return SensCardStat.leak_sensor & 0xFFFF;
      case SIDECAR_TEMPERATURE:
        return SensCardStat.temperature & 0xFFFF;
      case SIDECAR_HUMIDITY:
        return SensCardStat.humidity & 0xFFFF;
      case SIDECAR_RESERVED_1:
        return 0;
      case SIDECAR_RESERVED_2:
        return 0;
      case SIDECAR_RESERVED_3:
        return 0;
      case SIDECAR_RESERVED_4:
        return 0;
      case SIDECAR_RESERVED_5:
        return 0;
      case SIDECAR_RESERVED_6:
        return 0;
      case SIDECAR_RESERVED_7:
        return 0;
      default:
        return 0;
    }
  } else {
    return ILLIGAL_FUNC << 16;
  }
}

uint32_t SideCar_Sens_DevCtrl_Handler(RsFunc_t func, uint16_t addr, uint16_t data, uint8_t len, bool root) {
  if (func == READ_HOLDING_REGISTERS) {
    switch (addr) {
      case SIDECAR_PRESSURE_PUMP:
        return SensCardCtrl.pressure_pump & 0xFFFF;
      case SIDECAR_RESERVED_CTRL_1:
        return 0;
      case SIDECAR_RESERVED_CTRL_2:
        return 0;
      case SIDECAR_RESERVED_CTRL_3:
        return 0;
      case SIDECAR_RESERVED_CTRL_4:
        return 0;
      case SIDECAR_RESERVED_CTRL_5:
        return 0;
      case SIDECAR_RESERVED_CTRL_6:
        return 0;
      case SIDECAR_RESERVED_CTRL_7:
        return 0;
      case SIDECAR_RESERVED_CTRL_8:
        return 0;
      case SIDECAR_RESERVED_CTRL_9:
        return 0;
      case SIDECAR_RESERVED_CTRL_10:
        return 0;
      case SIDECAR_RESERVED_CTRL_11:
        return 0;
      case SIDECAR_RESERVED_CTRL_12:
        return 0;
      case SIDECAR_RESERVED_CTRL_13:
        return 0;
      case SIDECAR_RESERVED_CTRL_14:
        return 0;
      case SIDECAR_RESERVED_CTRL_15:
        return 0;
      default:
        return 0;
    }
  } else if (func == WRITE_SINGLE_REGISTER || func == WRITE_MULTIPLE_REGISTERS) {
    if (root) {
      switch (addr) {
        case SIDECAR_PRESSURE_PUMP:
          return (SensCardCtrl.pressure_pump = data) & 0xFFFF;
        case SIDECAR_RESERVED_CTRL_1:
          return 0;
        case SIDECAR_RESERVED_CTRL_2:
          return 0;
        case SIDECAR_RESERVED_CTRL_3:
          return 0;
        case SIDECAR_RESERVED_CTRL_4:
          return 0;
        case SIDECAR_RESERVED_CTRL_5:
          return 0;
        case SIDECAR_RESERVED_CTRL_6:
          return 0;
        case SIDECAR_RESERVED_CTRL_7:
          return 0;
        case SIDECAR_RESERVED_CTRL_8:
          return 0;
        case SIDECAR_RESERVED_CTRL_9:
          return 0;
        case SIDECAR_RESERVED_CTRL_10:
          return 0;
        case SIDECAR_RESERVED_CTRL_11:
          return 0;
        case SIDECAR_RESERVED_CTRL_12:
          return 0;
        case SIDECAR_RESERVED_CTRL_13:
          return 0;
        case SIDECAR_RESERVED_CTRL_14:
          return 0;
        case SIDECAR_RESERVED_CTRL_15:
          return 0;
        default:
          return ILLIGAL_DATA_ADDR << 16;
      }
    } else {
      return ILLIGAL_FUNC << 16;
    }
  } else {
    return ILLIGAL_FUNC << 16;
  }
}