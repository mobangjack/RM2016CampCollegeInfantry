#ifndef __NRF_TASK_H__
#define __NRF_TASK_H__

typedef enum
{
	NRF_MODE_IDLE = 0x00,
	NRF_MODE_RX = 0x01,
	NRF_MODE_TX = 0x02,
}NRFMode;

void NRFTask(void);

extern NRFMode nrfMode;

#endif

