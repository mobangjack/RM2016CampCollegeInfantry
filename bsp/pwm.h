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
 
#ifndef __PWM_H__
#define __PWM_H__

#define PWM1 TIM3->CCR1
#define PWM2 TIM3->CCR2
#define PWM3 TIM3->CCR3
#define PWM4 TIM3->CCR4
#define PWM5 TIM4->CCR1
#define PWM6 TIM4->CCR2
#define PWM7 TIM4->CCR3
#define PWM8 TIM4->CCR4

void PWM_Config(void);

#endif

