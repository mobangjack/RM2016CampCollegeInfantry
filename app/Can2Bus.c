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

Encoder CM1Encoder = {0};
Encoder CM2Encoder = {0};
Encoder CM3Encoder = {0};
Encoder CM4Encoder = {0};
Encoder GMYEncoder = {0};
Encoder GMPEncoder = {0};

void Can2BusTask(void)
{   
	uint16_t value = (can2RxMsg.Data[0]<<8) | can2RxMsg.Data[1];
	switch(can2RxMsg.StdId)
	{
		case MOTOR1_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&CM1Encoder, value);
		}break;
		case MOTOR2_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&CM2Encoder, value);
		}break;
		case MOTOR3_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&CM3Encoder, value); 
		}break;
		case MOTOR4_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&CM4Encoder, value);
		}break;
		case MOTOR5_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&GMYEncoder, value);
		}break;
		case MOTOR6_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&GMPEncoder, value);
		}break;
		case ZGYRO_FEEDBACK_CAN_MSG_ID:
		{
			ZGyroAngle = -0.01f*((int32_t)(can2RxMsg.Data[0]<<24)|(int32_t)(can2RxMsg.Data[1]<<16) | (int32_t)(can2RxMsg.Data[2]<<8) | (int32_t)(can2RxMsg.Data[3]));
			
		}break;		
		default:
		{
		}break;
	}
}
