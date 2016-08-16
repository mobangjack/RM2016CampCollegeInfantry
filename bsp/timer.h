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
 
#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

void TIM6_Config(void);
void TIM2_Config(void);

void TIM6_Start(void);
void TIM2_Start(void);

void TIM6_Stop(void);
void TIM2_Stop(void);

uint32_t Micros(void);

#endif
