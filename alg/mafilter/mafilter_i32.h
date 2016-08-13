/**
 * Copyright (c) 2011-2016, Mobangjack 莫帮杰 (mobangjack@foxmail.com).
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

#ifndef __MAFILTER_H__
#define __MAFILTER_H__

#ifdef __cpluplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
	
typedef struct
{
	int32_t* buf;
	uint32_t len;
	int32_t det;
	uint32_t ptr;
	int32_t sum;
	int32_t out;
}MAFilterI32;

void MAFilterI32_Init(MAFilterI32* mafilter, int32_t* buf, uint32_t len);
MAFilterI32* MAFilterI32_Create(uint32_t len);
int32_t MAFilterI32_Calc(MAFilterI32* mafilter, int32_t v);
void MAFilterI32_Reset(MAFilterI32* mafilter);

#ifdef __cpluplus
}
#endif

#endif
