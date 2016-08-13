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
 
#include "pid.h"

void PID_Reset(PID *pid)
{
	pid->err[0] = 0;
	pid->err[1] = 0;
	pid->componentKp = 0;
	pid->componentKi = 0;
	pid->componentKd = 0;
	pid->output = 0;
}

#define limit(val,min,max) (val=val>max?max:(val<min?min:val))
void PID_Calc(PID *pid)
{
	pid->err[1] = pid->ref - pid->fdb; // calculate error
	pid->componentKp = (pid->kp + pid->kp_offset) * pid->err[1]; // P
	limit(pid->componentKp, -pid->componentKpMax, pid->componentKpMax);
	pid->componentKi+= (pid->ki + pid->ki_offset) * pid->err[1]; // I
	limit(pid->componentKi, -pid->componentKiMax, pid->componentKiMax);
	pid->componentKd = (pid->kd + pid->kd_offset) * (pid->err[1] - pid->err[0]); // D
	limit(pid->componentKd, -pid->componentKdMax, pid->componentKdMax);
	pid->output = pid->componentKp + pid->componentKi + pid->componentKd; // output
	limit(pid->output, -pid->outputMax, pid->outputMax);
	pid->err[0] = pid->err[1]; // err fifo
}

