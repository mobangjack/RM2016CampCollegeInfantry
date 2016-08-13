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
 
#ifndef __ODOM_TASK_H__
#define __ODOM_TASK_H__

#include <stdint.h>
#include <string.h>
#include "crc16.h"
	
#define ODOM_HEADER 0xabcd  
#define ODOM_INIT_CRC16 0xdcba
#define ODOM_SIZE 16

#pragma pack(1)
typedef struct
{
	uint16_t header : 16;
	int16_t px : 16;
	int16_t py : 16;
	int16_t pz : 16;
	int16_t vx : 16;
	int16_t vy : 16;
	int16_t vz : 16;
	uint16_t check_sum : 16;
}Odom;

void OdomTask(void);

extern Odom odom;

#endif
