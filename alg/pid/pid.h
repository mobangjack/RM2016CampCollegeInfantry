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
 
#ifndef __PID_H__
#define __PID_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdint.h>
	
typedef struct PID
{
	float ref;
	float fdb;
	float err[2];
	float kp;
	float ki;
	float kd;
	float componentKp;
	float componentKi;
	float componentKd;
	float componentKpMax;
	float componentKiMax;
	float componentKdMax;
	float output;
	float outputMax;
	float kp_offset;
	float ki_offset;
	float kd_offset;
	void (*Calc)(struct PID *pid);
	void (*Reset)(struct PID *pid);
}PID;

void PID_Reset(PID *pid);
void PID_Calc(PID *pid);

#define PID_CREATE(KP,KI,KD,PM,IM,DM,OM) \
{\
	.ref = 0,\
	.fdb = 0,\
	.err = {0,0},\
	.kp = KP,\
	.ki = KI,\
	.kd = KD,\
	.componentKp = 0,\
	.componentKi = 0,\
	.componentKd = 0,\
	.componentKpMax = PM,\
	.componentKiMax = IM,\
	.componentKdMax = DM,\
	.output = 0,\
	.outputMax = OM,\
	.kp_offset = 0,\
	.ki_offset = 0,\
	.kd_offset = 0,\
	&PID_Calc,\
	&PID_Reset,\
}\

#ifdef __cplusplus
}
#endif
	
#endif

