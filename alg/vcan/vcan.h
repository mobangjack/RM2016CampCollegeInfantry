#ifndef __VCAN_H__
#define __VCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "crc16.h"

typedef struct
{
	uint8_t header;
	uint8_t id;
	uint8_t data[8];
}VCan;

uint8_t VCan_Tx(VCan* vcan);
uint8_t VCan_Rx(VCan* vcan);

#ifdef __cplusplus
}
#endif

#endif


