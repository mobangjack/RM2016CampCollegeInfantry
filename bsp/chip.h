#ifndef __CHIP_H__
#define __CHIP_H__

#include "stm32f4xx.h"

void GPIO_Config(GPIO_TypeDef* gpiox, u32 pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, GPIOOType_TypeDef otype, GPIOPuPd_TypeDef pupd);
void TIM_Config(TIM_TypeDef* timx, u16 prescaler, u16 counter_mode, u32 period, u16 clock_division, u8 repetition_counter);
void TIM_OC_Config(TIM_TypeDef* timx, u8 channel, u16 mode, u16 optState, u16 optNewState, u32 pulse, u16 polarity, u16 newPolarity, u16 idleState, u16 newIdleState);
void NVIC_Config(u8 channel, u8 preemption_priority, u8 subpriority);
void USART_Config(USART_TypeDef* usartx, u32 baudrate, u16 word_length, u16 stopbits, u16 parity, u16 mode, u16 flow_control);
void CAN_Config(CAN_TypeDef* canx, u16 prescaler, u8 mode, u8 sjw, u8 bs1, u8 bs2, FunctionalState ttcm, FunctionalState abom, FunctionalState awum, FunctionalState nart, FunctionalState rflm, FunctionalState txfp);
void CAN_Filter_Config(u16 id_high, u16 id_low, u16 mask_id_high, u16 mask_id_low, u16 fifo, u8 number, u8 mode, u8 scale);
void DMA_Config(DMA_Stream_TypeDef* DMAy_Streamx, u32 channel, u32 pba, u32 mba, u32 dir, u32 bufSize);
void EXIT_Config(u32 line, EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger);

#endif

