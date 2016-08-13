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
 
#include "ramp.h"

void Ramp_Init(Ramp* ramp, uint32_t scale)
{
	ramp->scale = scale;
}

float Ramp_Calc(Ramp* ramp)
{
	if(ramp->dir == RAMP_DIR_UP)
	{
		if(ramp->count < ramp->scale)
		{
			ramp->count++;
		}
	}
	else
	{
		if(ramp->count > 0)
		{
			ramp->count--;
		}
	}
	ramp->output = ramp->count / (float)ramp->scale;
	return ramp->output;
}

void Ramp_SetCounter(Ramp* ramp, uint32_t count)
{
	ramp->count = count;
}

void Ramp_ResetCounter(Ramp* ramp)
{
	ramp->count = (ramp->dir == RAMP_DIR_UP) ? 0 : ramp->scale;
}

void Ramp_SetScale(Ramp* ramp, uint32_t scale)
{
	ramp->scale = scale;
}

uint8_t Ramp_IsOverflow(Ramp* ramp)
{
	return (ramp->dir == RAMP_DIR_UP) ? (ramp->count >= ramp->scale) : (ramp->count <= ramp->scale);
}

uint8_t Ramp_GetDir(Ramp* ramp)
{
	return ramp->dir;
}

void Ramp_SetDir(Ramp* ramp, uint8_t dir)
{
	ramp->dir = dir;
}

