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

WorkingState workingState = WORKING_STATE_PREPARE;
WorkingState lastWorkingState = WORKING_STATE_PREPARE;

Mecanum mecanumPosition;
Mecanum mecanumSpeed;
Mecanum mecanumCurrent;

PID chassisPositionXPid = CHASSIS_POSITION_PID_DEFAULT;
PID chassisPositionYPid = CHASSIS_POSITION_PID_DEFAULT;
PID chassisPositionZPid = CHASSIS_POSITION_PID_DEFAULT;
PID chassisSpeedXPid = CHASSIS_SPEED_PID_DEFAULT;
PID chassisSpeedYPid = CHASSIS_SPEED_PID_DEFAULT;
PID chassisSpeedZPid = CHASSIS_SPEED_PID_DEFAULT;

PID gimbalsPositionYawPID = GIMBALS_POSITION_PID_DEFAULT;
PID gimbalsPositionPitchPID = GIMBALS_POSITION_PID_DEFAULT;
PID gimbalsSpeedYawPID = GIMBALS_SPEED_PID_DEFAULT;
PID gimbalsSpeedPitchPID = GIMBALS_SPEED_PID_DEFAULT;

Ramp chassisRamp = CHASSIS_RAMP_DEFAULT;
Ramp gimbalsRamp = GIMBALS_RAMP_DEFAULT;

ChassisMotorCurrent chassisMotorCurrent;
GimbalsMotorCurrent gimbalsMotorCurrent;

void WorkingStateSM(void)
{
	lastWorkingState = workingState;
	if(inputMode == INPUT_MODE_NO)
	{
		workingState = WORKING_STATE_STOP;
		return;
	}
	switch(workingState)
	{
		case WORKING_STATE_PREPARE:
		{
			if(Encoder_IsOk(&CM1Encoder) && Encoder_IsOk(&CM2Encoder) && Encoder_IsOk(&CM3Encoder) && Encoder_IsOk(&CM4Encoder))
			{
				workingState = WORKING_STATE_NORMAL;
			}
		}break;
		case WORKING_STATE_NORMAL:
		{
			if(!(Encoder_IsOk(&CM1Encoder) && Encoder_IsOk(&CM2Encoder) && Encoder_IsOk(&CM3Encoder) && Encoder_IsOk(&CM4Encoder)))
			{
				workingState = WORKING_STATE_PREPARE;
			}
		}break;
		case WORKING_STATE_STOP:
		{
			if(inputMode != INPUT_MODE_NO)
			{
				workingState = WORKING_STATE_PREPARE;
			}
		}break;
		default:
		{
			workingState = WORKING_STATE_STOP;
		}break;
	}
}

void ChassisPositionControl(void)
{
	/* Mecanum Position Synthesis */
	mecanumPosition.w1 = CM1Encoder.rad;
	mecanumPosition.w2 = CM2Encoder.rad;
	mecanumPosition.w3 = CM3Encoder.rad;
	mecanumPosition.w4 = CM4Encoder.rad;
	
	Mecanum_Synthesis(&mecanumPosition);
	
	chassisPositionXPid.ref = chassisPosition.x;
	chassisPositionYPid.ref = chassisPosition.y;
	chassisPositionZPid.ref = chassisPosition.z;
	
	chassisPositionXPid.fdb = mecanumPosition.x;
	chassisPositionYPid.fdb = mecanumPosition.y;
	chassisPositionZPid.fdb = mecanumPosition.z;
	
	chassisPositionXPid.Calc(&chassisPositionXPid);
	chassisPositionYPid.Calc(&chassisPositionYPid);
	chassisPositionZPid.Calc(&chassisPositionZPid);
	
	chassisSpeed.x = chassisPositionXPid.output;
	chassisSpeed.y = chassisPositionYPid.output;
	chassisSpeed.z = chassisPositionZPid.output;
}

void ChassisSpeedControl(void)
{
	/* Mecanum Speed Synthesis */
	mecanumSpeed.w1 = CM1Encoder.rad_rate;
	mecanumSpeed.w2 = CM2Encoder.rad_rate;
	mecanumSpeed.w3 = CM3Encoder.rad_rate;
	mecanumSpeed.w4 = CM4Encoder.rad_rate;
	
	Mecanum_Synthesis(&mecanumSpeed);
	
	chassisSpeedXPid.ref = chassisSpeed.x;
	chassisSpeedYPid.ref = chassisSpeed.y;
	chassisSpeedZPid.ref = chassisSpeed.z;
	
	chassisSpeedXPid.fdb = mecanumSpeed.x;
	chassisSpeedYPid.fdb = mecanumSpeed.y;
	chassisSpeedZPid.fdb = mecanumSpeed.z;
	
	chassisSpeedXPid.Calc(&chassisSpeedXPid);
	chassisSpeedYPid.Calc(&chassisSpeedYPid);
	chassisSpeedZPid.Calc(&chassisSpeedZPid);
	
	chassisCurrent.x = chassisSpeedXPid.output;
	chassisCurrent.y = chassisSpeedYPid.output;
	chassisCurrent.z = chassisSpeedZPid.output;
}

void ChassisCurrentControl(void)
{
	mecanumCurrent.x = chassisCurrent.x;
	mecanumCurrent.y = chassisCurrent.y;
	mecanumCurrent.z = chassisCurrent.z;
	
	Mecanum_Decompose(&mecanumCurrent);
	
	chassisRamp.Calc(&chassisRamp);
	
	chassisMotorCurrent.m1 = mecanumCurrent.w1 * chassisRamp.output;
	chassisMotorCurrent.m2 = mecanumCurrent.w2 * chassisRamp.output;
	chassisMotorCurrent.m3 = mecanumCurrent.w3 * chassisRamp.output;
	chassisMotorCurrent.m4 = mecanumCurrent.w4 * chassisRamp.output;
}

void GimbalsPositionControl(void)
{
	gimbalsPositionYawPID.ref = gimbalsPosition.yaw;
	gimbalsPositionPitchPID.ref = gimbalsPosition.pit;
	
	gimbalsPositionYawPID.fdb = GMYEncoder.rate;
	gimbalsPositionPitchPID.fdb = GMPEncoder.rate;
	
	gimbalsPositionYawPID.Calc(&gimbalsPositionYawPID);
	gimbalsPositionPitchPID.Calc(&gimbalsPositionPitchPID);
	
	gimbalsSpeed.yaw = gimbalsPositionYawPID.output;
	gimbalsSpeed.pit = gimbalsPositionPitchPID.output;
}

void GimbalsSpeedControl(void)
{
	gimbalsSpeedYawPID.ref = gimbalsSpeed.yaw;
	gimbalsSpeedPitchPID.ref = gimbalsSpeed.pit;
	
	gimbalsSpeedYawPID.fdb = GMYEncoder.rate;
	gimbalsSpeedPitchPID.fdb = GMPEncoder.rate;
	
	gimbalsSpeedYawPID.Calc(&gimbalsSpeedYawPID);
	gimbalsSpeedPitchPID.Calc(&gimbalsSpeedPitchPID);
	
	gimbalsCurrent.yaw = gimbalsSpeedYawPID.output;
	gimbalsCurrent.pit = gimbalsSpeedPitchPID.output;
}

void GimbalsCurrentControl(void)
{
	gimbalsRamp.Calc(&gimbalsRamp);
	gimbalsMotorCurrent.yaw = gimbalsCurrent.yaw * gimbalsRamp.output;
	gimbalsMotorCurrent.pit = gimbalsCurrent.pit * gimbalsRamp.output;
}

void PID_ResetAll(void)
{
	PID_Reset(&chassisPositionXPid);
	PID_Reset(&chassisPositionYPid);
	PID_Reset(&chassisPositionZPid);
	PID_Reset(&gimbalsPositionYawPID);
	PID_Reset(&gimbalsPositionPitchPID);
	
	PID_Reset(&chassisSpeedXPid);
	PID_Reset(&chassisSpeedYPid);
	PID_Reset(&chassisSpeedZPid);
	PID_Reset(&gimbalsSpeedYawPID);
	PID_Reset(&gimbalsSpeedPitchPID);
}

void Encoder_ResetAll(void)
{
	Encoder_Reset(&CM1Encoder);
	Encoder_Reset(&CM2Encoder);
	Encoder_Reset(&CM3Encoder);
	Encoder_Reset(&CM4Encoder);
	Encoder_Reset(&GMYEncoder);
	Encoder_Reset(&GMPEncoder);
}

void Ramp_ResetAll(void)
{
	Ramp_ResetCounter(&chassisRamp);
	Ramp_ResetCounter(&gimbalsRamp);
}

void Controller_Reset(void)
{
	Encoder_ResetAll();
	Ramp_ResetAll();
	PID_ResetAll();
}

void ChassisMotorCurrentTransmit(void)
{
	SetCMCurrent(CAN2, chassisMotorCurrent.m1, chassisMotorCurrent.m2, chassisMotorCurrent.m3, chassisMotorCurrent.m4);
}

void GimbalsMotorCurrentTransmit(void)
{
	SetGMCurrent(CAN2, gimbalsMotorCurrent.yaw, gimbalsMotorCurrent.pit);
}

static uint32_t ms_tick = 0;
void ControlTask(void)
{
	ms_tick++;
	WorkingStateSM();
	if(lastWorkingState == WORKING_STATE_STOP && workingState == WORKING_STATE_PREPARE)
	{
		ms_tick = 0;
		Controller_Reset();
	}
	else if(workingState == WORKING_STATE_NORMAL)
	{
		if(lastCtrlMode != ctrlMode)
		{
			//Ramp_ResetAll();
			//PID_ResetAll();
		}
		switch(ctrlMode)
		{
			case CTRL_MODE_POSITION:
			{
				if(ms_tick % 4 == 0)
				{
					ChassisPositionControl();
					ChassisSpeedControl();
					ChassisCurrentControl();
					GimbalsPositionControl();
					GimbalsSpeedControl();
					GimbalsCurrentControl();
					ChassisMotorCurrentTransmit();
					GimbalsMotorCurrentTransmit();
				}
			}break;
			case CTRL_MODE_SPEED:
			{
				if(ms_tick % 4  == 0)
				{
					ChassisSpeedControl();
					ChassisCurrentControl();
					GimbalsSpeedControl();
					GimbalsCurrentControl();
					ChassisMotorCurrentTransmit();
					GimbalsMotorCurrentTransmit();
				}
			}break;
			case CTRL_MODE_CURRENT:
			{
				if(ms_tick % 4  == 0)
				{
					ChassisCurrentControl();
					GimbalsCurrentControl();
					ChassisMotorCurrentTransmit();
					GimbalsMotorCurrentTransmit();
				}
			}break;
			default:
			{
			}break;
		}
	}
	
}

