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
/*-PWM1---(PA0---TIM5_CH1)--*/
/*-PWM2---(PA1---TIM5_CH2)--*/
/*-PWM3---(PA2---TIM5_CH3)--*/
/*-PWM4---(PA8---TIM1_CH1)--*/
/*-PWM5---(PB4---TIM3_CH1)--*/
/*-PWM6---(PB5---TIM3_CH2)--*/

void PWM_Config(void)
{
    GPIO_InitTypeDef          gpio;
    TIM_TimeBaseInitTypeDef   tim;
    TIM_OCInitTypeDef         oc;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA ,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB ,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   //PCLK1=42MHz,TIM5 clk =84MHz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //PCLK1=42MHz,TIM2 clk =84MHz
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);

	gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOB,&gpio);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);	
	
	// TIM5
	tim.TIM_Prescaler = 84-1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 2500;   //2.5ms
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&tim);

	// TIM1
	tim.TIM_Prescaler = 168-1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 2500;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1,&tim);
	
	// TIM3
	tim.TIM_Prescaler = 84-1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 2500;   //2.5ms
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&tim);
	
	oc.TIM_OCMode = TIM_OCMode_PWM2;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OutputNState = TIM_OutputState_Disable;
	oc.TIM_Pulse = 1000;
	oc.TIM_OCPolarity = TIM_OCPolarity_Low;
	oc.TIM_OCNPolarity = TIM_OCPolarity_High;
	oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
	
	TIM_OC1Init(TIM5,&oc);
	TIM_OC2Init(TIM5,&oc);
	TIM_OC3Init(TIM5,&oc);
	TIM_OC1Init(TIM1,&oc);
	TIM_OC1Init(TIM3,&oc);
	TIM_OC2Init(TIM3,&oc);
	
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM5,ENABLE);
	TIM_Cmd(TIM1,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
}
