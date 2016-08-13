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
 
/****************************************/
/*        Moving Average Filter         */
/****************************************/

#ifndef __MAFILTER_F32_H__
#define __MAFILTER_F32_H__

#ifdef __cpluplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
	
typedef struct
{
	float* buf;
	uint32_t len;
	float det;
	uint32_t ptr;
	float sum;
	float out;
}MAFilterF32;

void MAFilterF32_Init(MAFilterF32* mafilter, float* buf, uint32_t len);
MAFilterF32* MAFilterF32_Create(uint32_t len);
float MAFilterF32_Calc(MAFilterF32* mafilter, float v);
void MAFilterF32_Reset(MAFilterF32* mafilter);

#ifdef __cpluplus
}
#endif

#endif
