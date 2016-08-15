#include "main.h"

NRFMode nrfMode = NRF_MODE_RX;

uint8_t rxBuf[RX_PLOAD_WIDTH] = {0};

void NRFTask(void)
{
	if(NRF24L01_Rx(rxBuf) == 0)
	{
		TX_Mode();
		NRF24L01_Tx(rxBuf);
		RX_Mode();
	}
}
