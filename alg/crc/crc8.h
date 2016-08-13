#ifndef __CRC8_H__
#define __CRC8_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	extern const uint8_t CRC8Table[256];
	extern const uint8_t INIT_CRC8;

	extern uint8_t CRC8Calc(uint8_t* msg, uint32_t len, uint8_t crc8);
	extern uint8_t CRC8Check(uint8_t* msg, uint32_t len, uint8_t crc8);
	extern uint8_t CRC8Append(uint8_t* msg, uint32_t len, uint8_t crc8);

#ifdef __cplusplus
}
#endif

#endif
