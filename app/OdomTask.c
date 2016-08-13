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

Odom odom;

void OdomTask(void)
{
	Mecanum mecanum;
	
	/* Velocity Synthesis */
	mecanum.w1 = CM1Encoder.rate_radian;
	mecanum.w2 = CM2Encoder.rate_radian;
	mecanum.w3 = CM3Encoder.rate_radian;
	mecanum.w4 = CM4Encoder.rate_radian;
	
	Mecanum_Synthesis(&mecanum);
	
	odom.vx = mecanum.x * 1000;
	odom.vy = mecanum.y * 1000;
	odom.vz = mecanum.z * 1000;
	
	/* Position Synthesis */
	mecanum.w1 = CM1Encoder.radian;
	mecanum.w2 = CM2Encoder.radian;
	mecanum.w3 = CM3Encoder.radian;
	mecanum.w4 = CM4Encoder.radian;
	
	Mecanum_Synthesis(&mecanum);
	
	odom.px = mecanum.x * 1000;
	odom.py = mecanum.y * 1000;
	odom.pz = mecanum.z * 1000;
	
	odom.header = ODOM_HEADER;
	
	CRC16Append((uint8_t*)&odom, sizeof(Odom), ODOM_INIT_CRC16);
	USART3_PrintBlock((uint8_t*)&odom, sizeof(Odom));
	
}

