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

#include "mafilter.h"

void MAFilter_Init(MAFilter* mafilter, Typedef* buf, uint32_t len)
{
	mafilter->buf = buf;
	mafilter->len = len;
	mafilter->det = 0;
	mafilter->ptr = 0;
	mafilter->sum = 0;
	mafilter->out = 0;
}

MAFilter* MAFilter_Create(uint32_t len)
{
	MAFilter* mafilter = (MAFilter*)malloc(sizeof(MAFilter));
	if(mafilter == NULL) return NULL;
	mafilter->buf = (Typedef*)malloc(sizeof(Typedef)*len);
	if(mafilter->buf == NULL) {free(mafilter); return NULL;}
	mafilter->len = len;
	for(mafilter->ptr = 0; mafilter->ptr < mafilter->len; mafilter->ptr++)
		mafilter->buf[mafilter->ptr] = 0;
	mafilter->det = 0;
	mafilter->ptr = 0;
	mafilter->sum = 0;
	mafilter->out = 0;
	return mafilter;
}

Typedef MAFilter_Calc(MAFilter* mafilter, Typedef v)
{
	mafilter->det = v - mafilter->buf[mafilter->ptr];
	mafilter->sum += mafilter->det;
	mafilter->out = mafilter->sum / mafilter->len;
	mafilter->buf[mafilter->ptr++] = v;
	if(mafilter->ptr == mafilter->len) mafilter->ptr = 0;
	return mafilter->out;
}

void MAFilter_Reset(MAFilter* mafilter)
{
	for(mafilter->ptr = 0; mafilter->ptr < mafilter->len; mafilter->ptr++)
		mafilter->buf[mafilter->ptr] = 0;
	mafilter->ptr = 0;
	mafilter->sum = 0;
	mafilter->out = 0;
}

