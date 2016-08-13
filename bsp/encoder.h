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
 
#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stdint.h>

#define ENCODER_VAL_MAX 8191           
#define ENCODER_DIFF_MAX 7500          
#define ENCODER_RATE_BUF_SIZE 10       
#define ENCODER_INIT_FRAME_COUNT 100

typedef struct Encoder
{
	uint16_t value;
	uint16_t last_value;
	int32_t diff;
	uint16_t bias;
	int32_t round;
	int32_t scale;
	float angle;
	float radian;
	int32_t rate_raw;
	int32_t rate_buf[ENCODER_RATE_BUF_SIZE];
	uint8_t rate_cnt;
	uint8_t rate_ptr;
	int32_t rate_sum;
	int32_t rate;
	float rate_angle;
	float rate_radian;
	uint32_t cnt;
}Encoder;

void Encoder_Process(Encoder* encoder, uint16_t value);
uint8_t Encoder_IsOk(Encoder* encoder);
void Encoder_Reset(Encoder* encoder);

#endif
