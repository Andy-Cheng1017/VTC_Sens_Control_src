#ifndef __RS485_REGION_H_
#define __RS485_REGION_H_
#include <stdint.h>
#include "RS485.h"

#define SENS_CARD_DATAREAD_REG_START 0x0070
#define SENS_CARD_REG_END 0x007F
#define SENS_CARD_TOTAL_REG_NUM (SENS_CARD_REG_END - SENS_CARD_DATAREAD_REG_START + 1)

#define SENS_CARD_DEVCTRL_REG_START 0x0090
#define SENS_CARD_DEVCTRL_REG_END 0x009F
#define SENS_CARD_DEVCTRL_TOTAL_REG_NUM (SENS_CARD_DEVCTRL_REG_END - SENS_CARD_DEVCTRL_REG_START + 1)

uint32_t SideCar_Sens_DataRead_Handler(RsFunc_t func, uint16_t addr, uint16_t data, uint8_t len, bool root);
uint32_t SideCar_Sens_DevCtrl_Handler(RsFunc_t func, uint16_t addr, uint16_t data, uint8_t len, bool root);

#endif  // __RS485_REGION_H_