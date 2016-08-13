#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc32.h"

#define POLYNOMIAL 0x04c11db7L      // Standard CRC-32 polynomial

static uint32_t CRC32Table[256];    // Table of 8-bit remainders
static uint8_t tab_gen_flag = 0;

void CRC32GenTab(void)
{
	register uint16_t i, j;
	register uint32_t crc32;
	if (tab_gen_flag) {
		return;
	}
	for (i=0;  i<256;  i++)
	{
		crc32 = ((uint32_t)i << 24);
		for ( j = 0;  j < 8;  j++ )
		{
			if (crc32 & 0x80000000L)
				crc32 = (crc32 << 1) ^ POLYNOMIAL;
			else
				crc32 = (crc32 << 1);
		}
		CRC32Table[i] = crc32;
		//printf("%x, ", crc32);
	}
	tab_gen_flag = 1;
}

const uint32_t INIT_CRC32 = (uint32_t)(-1);

uint32_t CRC32Calc(uint8_t* msg, uint32_t len, uint32_t crc32)
{
	if (msg == 0 || len < sizeof(uint32_t))
		return 0;

	while (len--)
	{
		crc32 = (crc32 << 8) ^ CRC32Table[((crc32 >> 24) ^ *msg++) & 0xFF];
	}
	crc32 = ~crc32;
	memcpy(msg + len - sizeof(uint32_t), &crc32, sizeof(uint32_t));

	return crc32;
}

uint32_t CRC32Check(uint8_t* msg, uint32_t len, uint32_t crc32)
{
	if ((msg == 0) || (len <= sizeof(uint32_t)))
		return 0;
	crc32 = CRC32Calc(msg, len - sizeof(uint32_t), crc32);
	return crc32 == (uint32_t)(*(msg + len - sizeof(uint32_t)));
}

uint32_t CRC32Append(uint8_t* msg, uint32_t len, uint32_t crc32)
{
	crc32 = CRC32Calc(msg, len, crc32);
	memcpy(msg+len-sizeof(uint32_t), (uint8_t*)&crc32, sizeof(uint32_t));
	return crc32;
}
