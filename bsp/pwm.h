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

#define PWM1 TIM5->CCR1
#define PWM2 TIM5->CCR2
#define PWM3 TIM5->CCR3
#define PWM4 TIM1->CCR1
#define PWM5 TIM3->CCR1
#define PWM6 TIM3->CCR2

#define SET_FAN_SPEED(speed) (PWM1=speed)
#define SET_AIR_SPEED(speed) (PWM2=speed)
#define SET_BIN_SPEED(speed) (PWM3=speed)

#define FAN_ON()  SET_FAN_SPEED(1600)
#define FAN_OFF() SET_FAN_SPEED(1000)
#define AIR_ON()  SET_AIR_SPEED(1600)
#define AIR_OFF() SET_AIR_SPEED(1000)
#define BIN_ON()  SET_BIN_SPEED(1600)
#define BIN_OFF() SET_BIN_SPEED(1000)

void PWM_Config(void);

#endif

