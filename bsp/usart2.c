/**
 * Copyright (c) 2011-2016, Mobangjack Äª°ï½Ü (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "main.h"

/*-----USART2_TX-----PA2-----*/
/*-----USART2_RX-----PA3-----*/

FIFO* usart2_tx_fifo = NULL;

void USART2_Config(void)
{
    USART_InitTypeDef usart;
    GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); 

    gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA,&gpio);

    usart.USART_BaudRate = 38400;          // speed 10byte/ms
    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
    usart.USART_Parity = USART_Parity_No;
    usart.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2,&usart);

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2,ENABLE);

    nvic.NVIC_IRQChannel = USART2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&nvic);

	if(usart2_tx_fifo == NULL)
	{
		usart2_tx_fifo = FIFO_Create(USART2_TX_FIFO_SIZE);
	}
}


void USART2_Print(uint8_t ch)
{    
    FIFO_Push(usart2_tx_fifo, ch);
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

void USART2_PrintString(const char* str)
{
	while(*str != '\0')
	{
		FIFO_Push(usart2_tx_fifo, *str++);
	}
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

void USART2_PrintBlock(uint8_t* pdata, uint8_t len)
{
	FIFO_PushBlock(usart2_tx_fifo, pdata, len);
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

uint8_t usart2_rx_data;
void USART2_IRQHandler(void)
{  
    if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
    {   
		if(!FIFO_IsEmpty(usart2_tx_fifo))
		{
			uint8_t tx_data;
			FIFO_Pop(usart2_tx_fifo, &tx_data);
			USART_SendData(USART2, tx_data);
		}
		else
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		}
    }
	else if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        usart2_rx_data = USART_ReceiveData(USART2);
    }       
}

