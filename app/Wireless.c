#include "main.h"

WirelessMode wirelessMode = WIRELESS_MODE_IDLE;

uint8_t nrf_rx_buf[RX_PLOAD_WIDTH] = {0};

void WirelessTask(void)
{
	if(NRF24L01_Rx(nrf_rx_buf) == 0)
	{
		//TX_Mode();
		//NRF24L01_Tx(nrf_rx_buf);
		//RX_Mode();
		//USART2_PrintBlock(nrf_rx_buf, RX_PLOAD_WIDTH);
		LED_TOGGLE();
	}
}
