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
 
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdint.h>
#include "stm32f4xx.h"

#define CHASSIS_MOTOR_ANGULAR_SPEED_MAX 50

#define CHASSIS_MOTOR_CAN_TX_MSG_ID 0x200
#define GIMBALS_MOTOR_CAN_TX_MSG_ID 0x1ff

#define MOTOR1_FEEDBACK_CAN_MSG_ID  0x201
#define MOTOR2_FEEDBACK_CAN_MSG_ID  0x202 
#define MOTOR3_FEEDBACK_CAN_MSG_ID  0x203
#define MOTOR4_FEEDBACK_CAN_MSG_ID  0x204
#define MOTOR5_FEEDBACK_CAN_MSG_ID  0x205
#define MOTOR6_FEEDBACK_CAN_MSG_ID  0x206

void SetCMCurrent(CAN_TypeDef *CANx, int16_t c201, int16_t c202, int16_t c203, int16_t c204);
void SetGMCurrent(CAN_TypeDef *CANx, int16_t c205, int16_t c206);

#endif
