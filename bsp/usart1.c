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

uint8_t usart1_dma_rx_buf[2][USART1_DMA_RX_BUF_SIZE];
uint8_t* dbuf = usart1_dma_rx_buf[0];
DBUS dbus;

void USART1_Config(void)
{
    GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart;
	NVIC_InitTypeDef nvic;
    DMA_InitTypeDef dma;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
    
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
    
    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = GPIO_Pin_7;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &gpio);
    
    USART_DeInit(USART1);
    USART_StructInit(&usart);
    usart.USART_BaudRate = 100000;
    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
    usart.USART_Parity = USART_Parity_Even;
    usart.USART_Mode = USART_Mode_Rx;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &usart);
    
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    
    DMA_DeInit(DMA2_Stream2);
    DMA_StructInit(&dma);
    dma.DMA_Channel = DMA_Channel_4;
    dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
    dma.DMA_Memory0BaseAddr = (uint32_t)&usart1_dma_rx_buf[0][0];
    dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
    dma.DMA_BufferSize = sizeof(usart1_dma_rx_buf)/2;
    dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma.DMA_Mode = DMA_Mode_Circular;
    dma.DMA_Priority = DMA_Priority_Medium;
    dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream2, &dma);
    
    DMA_DoubleBufferModeConfig(DMA2_Stream2, (uint32_t)&usart1_dma_rx_buf[1][0], DMA_Memory_0);   //first used memory configuration
    DMA_DoubleBufferModeCmd(DMA2_Stream2, ENABLE);
    
    DMA_Cmd(DMA2_Stream2, ENABLE);
    
    nvic.NVIC_IRQChannel = USART1_IRQn;                          
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;		    
	nvic.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&nvic);	
    
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); // 14mspf
    USART_Cmd(USART1, ENABLE);

}

void USART1_IRQHandler(void)
{
	static uint32_t this_time_rx_len = 0;
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//clear the idle pending flag 
		(void)USART1->SR;
		(void)USART1->DR;

		DMA_Cmd(DMA2_Stream2, DISABLE);
		this_time_rx_len = USART1_DMA_RX_BUF_SIZE - DMA_GetCurrDataCounter(DMA2_Stream2);
		DMA2_Stream2->NDTR = (uint16_t)USART1_DMA_RX_BUF_SIZE;     //relocate the dma memory pointer to the beginning position
		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
		{
			dbuf = usart1_dma_rx_buf[0];
			DMA2_Stream2->CR |= (uint32_t)(DMA_SxCR_CT);        //enable the current selected memory is Memory 1
		}
		else
		{
			dbuf = usart1_dma_rx_buf[1];
			DMA2_Stream2->CR &= ~(uint32_t)(DMA_SxCR_CT);       //enable the current selected memory is Memory 0
		}
		DMA_Cmd(DMA2_Stream2, ENABLE);
		if(this_time_rx_len == RC_FRAME_LEN)
		{
			DBUS_DEC(&dbus, dbuf);
			InputTask();
		}
	}       
}

