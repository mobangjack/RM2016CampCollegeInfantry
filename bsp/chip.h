#ifndef __CHIP_H__
#define __CHIP_H__

#include "stm32f4xx.h"

typedef struct
{
	GPIO_TypeDef* grp;
	uint16_t pin;
}GPIO;

#define PA0 {GPIOA, GPIO_Pin_0}
#define PA1 {GPIOA, GPIO_Pin_1}
#define PA2 {GPIOA, GPIO_Pin_2}
#define PA3 {GPIOA, GPIO_Pin_3}
#define PA4 {GPIOA, GPIO_Pin_4}
#define PA5 {GPIOA, GPIO_Pin_5}
#define PA6 {GPIOA, GPIO_Pin_6}
#define PA7 {GPIOA, GPIO_Pin_7}
#define PA8 {GPIOA, GPIO_Pin_8}
#define PA9 {GPIOA, GPIO_Pin_9}
#define PA10 {GPIOA, GPIO_Pin_10}
#define PA11 {GPIOA, GPIO_Pin_11}
#define PA12 {GPIOA, GPIO_Pin_12}
#define PA13 {GPIOA, GPIO_Pin_13}
#define PA14 {GPIOA, GPIO_Pin_14}
#define PA15 {GPIOA, GPIO_Pin_15}

#define PB0 {GPIOB, GPIO_Pin_0}
#define PB1 {GPIOB, GPIO_Pin_1}
#define PB2 {GPIOB, GPIO_Pin_2}
#define PB3 {GPIOB, GPIO_Pin_3}
#define PB4 {GPIOB, GPIO_Pin_4}
#define PB5 {GPIOB, GPIO_Pin_5}
#define PB6 {GPIOB, GPIO_Pin_6}
#define PB7 {GPIOB, GPIO_Pin_7}
#define PB8 {GPIOB, GPIO_Pin_8}
#define PB9 {GPIOB, GPIO_Pin_9}
#define PB10 {GPIOB, GPIO_Pin_10}
#define PB11 {GPIOB, GPIO_Pin_11}
#define PB12 {GPIOB, GPIO_Pin_12}
#define PB13 {GPIOB, GPIO_Pin_13}
#define PB14 {GPIOB, GPIO_Pin_14}
#define PB15 {GPIOB, GPIO_Pin_15}

#define PC0 {GPIOC, GPIO_Pin_0}
#define PC1 {GPIOC, GPIO_Pin_1}
#define PC2 {GPIOC, GPIO_Pin_2}
#define PC3 {GPIOC, GPIO_Pin_3}
#define PC4 {GPIOC, GPIO_Pin_4}
#define PC5 {GPIOC, GPIO_Pin_5}
#define PC6 {GPIOC, GPIO_Pin_6}
#define PC7 {GPIOC, GPIO_Pin_7}
#define PC8 {GPIOC, GPIO_Pin_8}
#define PC9 {GPIOC, GPIO_Pin_9}
#define PC10 {GPIOC, GPIO_Pin_10}
#define PC11 {GPIOC, GPIO_Pin_11}
#define PC12 {GPIOC, GPIO_Pin_12}
#define PC13 {GPIOC, GPIO_Pin_13}
#define PC14 {GPIOC, GPIO_Pin_14}
#define PC15 {GPIOC, GPIO_Pin_15}

#define PD0 {GPIOD, GPIO_Pin_0}
#define PD1 {GPIOD, GPIO_Pin_1}
#define PD2 {GPIOD, GPIO_Pin_2}
#define PD3 {GPIOD, GPIO_Pin_3}
#define PD4 {GPIOD, GPIO_Pin_4}
#define PD5 {GPIOD, GPIO_Pin_5}
#define PD6 {GPIOD, GPIO_Pin_6}
#define PD7 {GPIOD, GPIO_Pin_7}
#define PD8 {GPIOD, GPIO_Pin_8}
#define PD9 {GPIOD, GPIO_Pin_9}
#define PD10 {GPIOD, GPIO_Pin_10}
#define PD11 {GPIOD, GPIO_Pin_11}
#define PD12 {GPIOD, GPIO_Pin_12}
#define PD13 {GPIOD, GPIO_Pin_13}
#define PD14 {GPIOD, GPIO_Pin_14}
#define PD15 {GPIOD, GPIO_Pin_15}

#define PE0 {GPIOE, GPIO_Pin_0}
#define PE1 {GPIOE, GPIO_Pin_1}
#define PE2 {GPIOE, GPIO_Pin_2}
#define PE3 {GPIOE, GPIO_Pin_3}
#define PE4 {GPIOE, GPIO_Pin_4}
#define PE5 {GPIOE, GPIO_Pin_5}
#define PE6 {GPIOE, GPIO_Pin_6}
#define PE7 {GPIOE, GPIO_Pin_7}
#define PE8 {GPIOE, GPIO_Pin_8}
#define PE9 {GPIOE, GPIO_Pin_9}
#define PE10 {GPIOE, GPIO_Pin_10}
#define PE11 {GPIOE, GPIO_Pin_11}
#define PE12 {GPIOE, GPIO_Pin_12}
#define PE13 {GPIOE, GPIO_Pin_13}
#define PE14 {GPIOE, GPIO_Pin_14}
#define PE15 {GPIOE, GPIO_Pin_15}

#define PF0 {GPIOF, GPIO_Pin_0}
#define PF1 {GPIOF, GPIO_Pin_1}
#define PF2 {GPIOF, GPIO_Pin_2}
#define PF3 {GPIOF, GPIO_Pin_3}
#define PF4 {GPIOF, GPIO_Pin_4}
#define PF5 {GPIOF, GPIO_Pin_5}
#define PF6 {GPIOF, GPIO_Pin_6}
#define PF7 {GPIOF, GPIO_Pin_7}
#define PF8 {GPIOF, GPIO_Pin_8}
#define PF9 {GPIOF, GPIO_Pin_9}
#define PF10 {GPIOF, GPIO_Pin_10}
#define PF11 {GPIOF, GPIO_Pin_11}
#define PF12 {GPIOF, GPIO_Pin_12}
#define PF13 {GPIOF, GPIO_Pin_13}
#define PF14 {GPIOF, GPIO_Pin_14}
#define PF15 {GPIOF, GPIO_Pin_15}

#define PG0 {GPIOG, GPIO_Pin_0}
#define PG1 {GPIOG, GPIO_Pin_1}
#define PG2 {GPIOG, GPIO_Pin_2}
#define PG3 {GPIOG, GPIO_Pin_3}
#define PG4 {GPIOG, GPIO_Pin_4}
#define PG5 {GPIOG, GPIO_Pin_5}
#define PG6 {GPIOG, GPIO_Pin_6}
#define PG7 {GPIOG, GPIO_Pin_7}
#define PG8 {GPIOG, GPIO_Pin_8}
#define PG9 {GPIOG, GPIO_Pin_9}
#define PG10 {GPIOG, GPIO_Pin_10}
#define PG11 {GPIOG, GPIO_Pin_11}
#define PG12 {GPIOG, GPIO_Pin_12}
#define PG13 {GPIOG, GPIO_Pin_13}
#define PG14 {GPIOG, GPIO_Pin_14}
#define PG15 {GPIOG, GPIO_Pin_15}

#define PH0 {GPIOH, GPIO_Pin_0}
#define PH1 {GPIOH, GPIO_Pin_1}
#define PH2 {GPIOH, GPIO_Pin_2}
#define PH3 {GPIOH, GPIO_Pin_3}
#define PH4 {GPIOH, GPIO_Pin_4}
#define PH5 {GPIOH, GPIO_Pin_5}
#define PH6 {GPIOH, GPIO_Pin_6}
#define PH7 {GPIOH, GPIO_Pin_7}
#define PH8 {GPIOH, GPIO_Pin_8}
#define PH9 {GPIOH, GPIO_Pin_9}
#define PH10 {GPIOH, GPIO_Pin_10}
#define PH11 {GPIOH, GPIO_Pin_11}
#define PH12 {GPIOH, GPIO_Pin_12}
#define PH13 {GPIOH, GPIO_Pin_13}
#define PH14 {GPIOH, GPIO_Pin_14}
#define PH15 {GPIOH, GPIO_Pin_15}

#define PI0 {GPIOI, GPIO_Pin_0}
#define PI1 {GPIOI, GPIO_Pin_1}
#define PI2 {GPIOI, GPIO_Pin_2}
#define PI3 {GPIOI, GPIO_Pin_3}
#define PI4 {GPIOI, GPIO_Pin_4}
#define PI5 {GPIOI, GPIO_Pin_5}
#define PI6 {GPIOI, GPIO_Pin_6}
#define PI7 {GPIOI, GPIO_Pin_7}
#define PI8 {GPIOI, GPIO_Pin_8}
#define PI9 {GPIOI, GPIO_Pin_9}
#define PI10 {GPIOI, GPIO_Pin_10}
#define PI11 {GPIOI, GPIO_Pin_11}
#define PI12 {GPIOI, GPIO_Pin_12}
#define PI13 {GPIOI, GPIO_Pin_13}
#define PI14 {GPIOI, GPIO_Pin_14}
#define PI15 {GPIOI, GPIO_Pin_15}

#define GPIO_Set(gpio)    GPIO_SetBits(gpio.grp, gpio.pin)
#define GPIO_Reset(gpio)  GPIO_ResetBits(gpio.grp, gpio.pin)
#define GPIO_Toggle(gpio) GPIO_ToggleBits(gpio.grp, gpio.pin)
#define GPIO_Read(gpio)   GPIO_ReadOutputDataBit(gpio.grp, gpio.pin)
#define GPIO_Write(gpio,v)  GPIO_WriteBit(gpio.grp, gpio.pin,v>0?Bit_SET:Bit_RESET)

void GPIO_Config(GPIO gpio, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, GPIOOType_TypeDef otype, GPIOPuPd_TypeDef pupd);
void TIM_Config(TIM_TypeDef* timx, u16 prescaler, u16 counter_mode, u32 period, u16 clock_division, u8 repetition_counter);
void TIM_OC_Config(TIM_TypeDef* timx, u8 channel, u16 mode, u16 optState, u16 optNewState, u32 pulse, u16 polarity, u16 newPolarity, u16 idleState, u16 newIdleState);
void NVIC_Config(u8 channel, u8 preemption_priority, u8 subpriority);
void USART_Config(USART_TypeDef* usartx, u32 baudrate, u16 word_length, u16 stopbits, u16 parity, u16 mode, u16 flow_control);
void CAN_Config(CAN_TypeDef* canx, u16 prescaler, u8 mode, u8 sjw, u8 bs1, u8 bs2, FunctionalState ttcm, FunctionalState abom, FunctionalState awum, FunctionalState nart, FunctionalState rflm, FunctionalState txfp);
void CAN_Filter_Config(u16 id_high, u16 id_low, u16 mask_id_high, u16 mask_id_low, u16 fifo, u8 number, u8 mode, u8 scale);
void DMA_Config(DMA_Stream_TypeDef* DMAy_Streamx, u32 channel, u32 pba, u32 mba, u32 dir, u32 bufSize);
void EXIT_Config(u32 line, EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger);

#endif

