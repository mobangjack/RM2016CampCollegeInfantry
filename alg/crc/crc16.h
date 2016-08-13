#ifndef __CRC16_H__
#define __CRC16_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint16_t CRC16Table[256];
extern const uint16_t INIT_CRC16;

extern uint16_t CRC16Calc(uint8_t* msg, uint32_t len, uint16_t crc16);
extern uint16_t CRC16Check(uint8_t* msg, uint32_t len, uint16_t crc16);
extern uint16_t CRC16Append(uint8_t* msg, uint32_t len, uint16_t crc16);

#ifdef __cplusplus
}
#endif

#endif
