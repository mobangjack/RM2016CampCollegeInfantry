#include "main.h"

uint8_t imu_it_flag = 0;

void MPU6050_IntConfiguration(void)
{
	GPIO_InitTypeDef    gpio;
    NVIC_InitTypeDef    nvic;
    EXTI_InitTypeDef    exti;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE);   
	gpio.GPIO_Pin = GPIO_Pin_5;
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
	
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,GPIO_PinSource5); 
	
    exti.EXTI_Line = EXTI_Line5;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling;
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
    
    nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

void EXTI9_5_IRQHandler(void)         //1KHz
{   
    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {    
        EXTI_ClearFlag(EXTI_Line5);          
        EXTI_ClearITPendingBit(EXTI_Line5);
        imu_it_flag = 1;
        GetPitchYawGxGyGz();
		//printf("it\n");
    }
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {    
        EXTI_ClearFlag(EXTI_Line6);          
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
    {    
        EXTI_ClearFlag(EXTI_Line7);          
        EXTI_ClearITPendingBit(EXTI_Line7);
    }
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
    {    
        EXTI_ClearFlag(EXTI_Line8);          
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
    {    
        EXTI_ClearFlag(EXTI_Line9);          
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
}

