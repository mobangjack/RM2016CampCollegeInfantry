#ifndef __WIRELESS_H__
#define __WIRELESS_H__

typedef enum
{
	WIRELESS_MODE_IDLE = 0x00,
	WIRELESS_MODE_RX = 0x01,
	WIRELESS_MODE_TX = 0x02,
}WirelessMode;

void WirelessTask(void);

extern WirelessMode wirelessMode;

#endif

