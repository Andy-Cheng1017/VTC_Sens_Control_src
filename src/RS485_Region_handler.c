#include "RS485_Region_handler.h"
#include "pressure_task.h"
#include "pt100_task.h"

uint32_t DataRead_Handler(RsFunc_t func, uint16_t addr, uint16_t data, uint8_t len, bool root) {
  if (func == READ_HOLDING_REGISTERS) {
    switch (addr) {
      case 0x0050:
        return (Pt100Stat.pt100_1_temp_m / 10) & 0xFFFF;
      case 0x0051:
        return (Pt100Stat.pt100_2_temp_m / 10) & 0xFFFF;
      case 0x0052:
        return (Pt100Stat.pt100_3_temp_m / 10) & 0xFFFF;
      case 0x0053:
        return (Pt100Stat.pt100_4_temp_m / 10) & 0xFFFF;
      case 0x0054:
        return (SensStat.press_1_val) & 0xFFFF;
      case 0x0055:
        return (SensStat.press_2_val) & 0xFFFF;
      case 0x0056:
        return SensStat.leak_sensor & 0xFFFF;
      case 0x0057:
        return SensStat.temperature & 0xFFFF;
      case 0x0058:
        return SensStat.humidity & 0xFFFF;
      default:
        return ILLIGAL_DATA_ADDR << 16;
    }
  } else {
    return ILLIGAL_FUNC << 16;
  }
}