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
	odom.header = ODOM_HEADER;
	
	odom.px = mecanumPosition.x * 1000;
	odom.py = mecanumPosition.y * 1000;
	odom.pz = mecanumPosition.z * 1000;
	
	odom.vx = mecanumSpeed.x * 1000;
	odom.vy = mecanumSpeed.y * 1000;
	odom.vz = mecanumSpeed.z * 1000;
	
	CRC16Append((uint8_t*)&odom, sizeof(Odom), ODOM_INIT_CRC16);
	USART3_PrintBlock((uint8_t*)&odom, sizeof(Odom));
	
}

