#ifndef __SPI1_H__
#define __SPI1_H__

#include "stm32f4xx.h"

#define RCC_SPI1_CLK                RCC_APB2Periph_SPI1
#define SPI1_GPIO_PORT              GPIOB
#define RCC_SPI1                    RCC_AHB1Periph_GPIOA
#define SPI1_SCK                    GPIO_Pin_5
#define SPI1_MISO                   GPIO_Pin_6
#define SPI1_MOSI                   GPIO_Pin_7
#define SPI1_SCK_SOURCE             GPIO_PinSource5
#define SPI1_MISO_SOURCE            GPIO_PinSource6
#define SPI1_MOSI_SOURCE            GPIO_PinSource7
																					  
void SPI1_Init(void);			 //初始化SPI口 
u8 SPI1_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif

