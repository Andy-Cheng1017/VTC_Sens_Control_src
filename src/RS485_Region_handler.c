#include "RS485_Region_handler.h"
#include "pressure_task.h"
#include "pt100_task.h"

uint32_t DataRead_Handler(RsFunc_t func, uint16_t addr, uint16_t data, uint8_t len, bool root) {
  if (func == READ_HOLDING_REGISTERS) {
    switch (addr) {
      case 0x0070:
        return (Pt100Stat.pt100_1_temp_m / 10) & 0xFFFF;
      case 0x0071:
        return (Pt100Stat.pt100_2_temp_m / 10) & 0xFFFF;
      case 0x0072:
        return (Pt100Stat.pt100_3_temp_m / 10) & 0xFFFF;
      case 0x0073:
        return (Pt100Stat.pt100_4_temp_m / 10) & 0xFFFF;
      case 0x0074:
        return (SensStat.press_1_val) & 0xFFFF;
      case 0x0075:
        return (SensStat.press_2_val) & 0xFFFF;
      case 0x0076:
        return SensStat.leak_sensor & 0xFFFF;
      case 0x0077:
        return SensStat.temperature & 0xFFFF;
      case 0x0078:
        return SensStat.humidity & 0xFFFF;
      case 0x0079:
        return 0;
      case 0x007A:
        return 0;
      case 0x007B:
        return 0;
      case 0x007C:
        return 0;
      case 0x007D:
        return 0;
      case 0x007E:
        return 0;
      case 0x007F:
        return 0;
      default:
        return ILLIGAL_DATA_ADDR << 16;
    }
  } else if (func == WRITE_SINGLE_REGISTER || func == WRITE_MULTIPLE_REGISTERS) {
    switch (addr) {
      case 0x0070:
        return 0;
      case 0x0071:
        return 0;
      case 0x0072:
        return 0;
      case 0x0073:
        return 0;
      case 0x0074:
        return 0;
      case 0x0075:
        return 0;
      case 0x0076:
        return 0;
      case 0x0077:
        return (SensStat.temperature = data) & 0xFFFF;
      case 0x0078:
        return (SensStat.humidity = data) & 0xFFFF;
      case 0x0079:
        return 0;
      case 0x007A:
        return 0;
      case 0x007B:
        return 0;
      case 0x007C:
        return 0;
      case 0x007D:
        return 0;
      case 0x007E:
        return 0;
      case 0x007F:
        return 0;
      default:
        return ILLIGAL_DATA_ADDR << 16;
    }
  } else {
    return ILLIGAL_FUNC << 16;
  }
}