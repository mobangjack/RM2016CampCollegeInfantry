#ifndef __CRC32_H__
#define __CRC32_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void CRC32GenTab(void);
extern const uint32_t INIT_CRC32;

extern uint32_t CRC32Calc(uint8_t* msg, uint32_t len, uint32_t crc32);
extern uint32_t CRC32Check(uint8_t* msg, uint32_t len, uint32_t crc32);
extern uint32_t CRC32Append(uint8_t* msg, uint32_t len, uint32_t crc32);

#ifdef __cplusplus
}
#endif

#endif
