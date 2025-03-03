#ifndef __RS485_REGION_H_
#define __RS485_REGION_H_
#include <stdint.h>
#include "RS485.h"

uint32_t DataRead_Handler(RsFunc_t func, uint16_t addr, uint16_t data, uint8_t len, bool root);

#endif  // __RS485_REGION_H_