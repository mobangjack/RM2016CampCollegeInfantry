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

InputMode inputMode = INPUT_MODE_NO;
InputMode lastInputMode = INPUT_MODE_NO;
CtrlMode ctrlMode = CTRL_MODE_SPEED;
CtrlMode lastCtrlMode = CTRL_MODE_SPEED;
SwitchPanel switchPanel;
Keyboard keyboard;

ChassisPosition chassisPosition;
ChassisSpeed chassisSpeed;
ChassisCurrent chassisCurrent;
GimbalsPosition gimbalsPosition;
GimbalsSpeed gimbalsSpeed;
GimbalsCurrent gimbalsCurrent;

MAFilterF32* mafilter_x = NULL;
MAFilterF32* mafilter_y = NULL;
MAFilterF32* mafilter_z = NULL;

void GetInputMode(void)
{
	lastInputMode = inputMode;
	switch(dbus.rc.s2)
	{
		case SW_UP:
		{
			inputMode = INPUT_MODE_RC;
		}break;
		case SW_MD:
		{
			inputMode = INPUT_MODE_HC;
		}break;
		case SW_DN:
		{
			inputMode = INPUT_MODE_NO;
		}break;
		default:
		{
			inputMode = INPUT_MODE_NO;
		}break;
	}
}

void GetCtrlMode(void)
{
	lastCtrlMode = ctrlMode;
	switch(dbus.rc.s1)
	{
		case SW_UP:
		{
			ctrlMode = CTRL_MODE_POSITION;
		}break;
		case SW_MD:
		{
			ctrlMode = CTRL_MODE_SPEED;
		}break;
		case SW_DN:
		{
			ctrlMode = CTRL_MODE_CURRENT;
		}break;
		default:
		{
			ctrlMode = CTRL_MODE_SPEED;
		}break;
	}
}

void GetSwitchState(SwitchState* s, uint8_t v)
{
	s->lastState = s->thisState;
	s->thisState = v;
	s->action = GET_SWITCH_ACTION(s->lastState, s->thisState);
}

void GetKeyAction(KeyState* k, uint8_t v)
{
	k->lastState = k->thisState;
	k->thisState = v;
	k->action = GET_KEY_ACTION(k->lastState, k->thisState);
}

void GetSwitchPanel(void)
{
	GetSwitchState(&switchPanel.s1, dbus.rc.s1);
	GetSwitchState(&switchPanel.s2, dbus.rc.s2);
}

void GetKeyboard(void)
{
	GetKeyAction(&keyboard.A, dbus.hc.key.val&KEY_A);
	GetKeyAction(&keyboard.D, dbus.hc.key.val&KEY_D);
	GetKeyAction(&keyboard.W, dbus.hc.key.val&KEY_W);
	GetKeyAction(&keyboard.S, dbus.hc.key.val&KEY_S);
	GetKeyAction(&keyboard.Shift, dbus.hc.key.val&KEY_SHIFT);
	GetKeyAction(&keyboard.Ctrl, dbus.hc.key.val&KEY_CTRL);
	GetKeyAction(&keyboard.Q, dbus.hc.key.val&KEY_Q);
	GetKeyAction(&keyboard.E, dbus.hc.key.val&KEY_E);
}


void GetStickCtrlChassisPosition(void)
{
	chassisPosition.x = MAP(dbus.rc.ch0, CH_MIN, CH_MAX, -INPUT_CHASSIS_POSITION_MAX, INPUT_CHASSIS_POSITION_MAX);
	chassisPosition.y = MAP(dbus.rc.ch1, CH_MIN, CH_MAX, -INPUT_CHASSIS_POSITION_MAX, INPUT_CHASSIS_POSITION_MAX);
	chassisPosition.z = MAP(dbus.rc.ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_POSITION_MAX, INPUT_GIMBALS_POSITION_MAX);
}

void GetStickCtrlChassisSpeed(void)
{
	chassisSpeed.x = MAP(dbus.rc.ch0, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
	chassisSpeed.y = MAP(dbus.rc.ch1, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
	chassisSpeed.z = MAP(dbus.rc.ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void GetStickCtrlChassisCurrent(void)
{
	chassisCurrent.x = MAP(dbus.rc.ch0, CH_MIN, CH_MAX, -INPUT_CHASSIS_CURRENT_MAX, INPUT_CHASSIS_CURRENT_MAX);
	chassisCurrent.y = MAP(dbus.rc.ch1, CH_MIN, CH_MAX, -INPUT_CHASSIS_CURRENT_MAX, INPUT_CHASSIS_CURRENT_MAX);
	chassisCurrent.z = MAP(dbus.rc.ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_CURRENT_MAX, INPUT_GIMBALS_CURRENT_MAX);
}

void GetStickCtrlGimbalsPosition(void)
{
	gimbalsPosition.yaw = MAP(dbus.rc.ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_POSITION_MAX, INPUT_GIMBALS_POSITION_MAX);
	gimbalsPosition.pit = MAP(dbus.rc.ch3, CH_MIN, CH_MAX, -INPUT_GIMBALS_POSITION_MAX, INPUT_GIMBALS_POSITION_MAX);
}

void GetStickCtrlGimbalsSpeed(void)
{
	gimbalsSpeed.yaw = MAP(dbus.rc.ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	gimbalsSpeed.pit = MAP(dbus.rc.ch3, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void GetStickCtrlGimbalsCurrent(void)
{
	gimbalsCurrent.yaw = MAP(dbus.rc.ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_CURRENT_MAX, INPUT_GIMBALS_CURRENT_MAX);
	gimbalsCurrent.pit = MAP(dbus.rc.ch3, CH_MIN, CH_MAX, -INPUT_GIMBALS_CURRENT_MAX, INPUT_GIMBALS_CURRENT_MAX);
}

void GetKeyboardCtrlChassisPosition(void)
{
	/**************************************/
	/*            ___________             */
	/*           /___________\            */
	/*          /             \           */
	/*     ____/               \____      */
	/*                                    */
	/**************************************/
	uint8_t key = dbus.hc.key.val;
	float position = (key & KEY_SHIFT) ? INPUT_CHASSIS_POSITION_MAX : INPUT_CHASSIS_POSITION_MAX / 2.f;
	float position_x = (key & KEY_A) ? -position : ((key & KEY_D) ? position : 0);
	float position_y = (key & KEY_S) ? -position : ((key & KEY_W) ? position : 0);
	float position_z = 500*MAP(dbus.hc.mouse.x, MS_MIN, MS_MAX, -INPUT_GIMBALS_POSITION_MAX, INPUT_GIMBALS_POSITION_MAX);
	if(mafilter_x == NULL) mafilter_x = MAFilterF32_Create(8);
	if(mafilter_y == NULL) mafilter_y = MAFilterF32_Create(8);
	if(mafilter_z == NULL) mafilter_z = MAFilterF32_Create(6);
	if(lastInputMode == INPUT_MODE_RC)
	{
		MAFilterF32_Reset(mafilter_x);
		MAFilterF32_Reset(mafilter_y);
		MAFilterF32_Reset(mafilter_z);
	}
	chassisPosition.x = MAFilterF32_Calc(mafilter_x, position_x);
	chassisPosition.y = MAFilterF32_Calc(mafilter_y, position_y);
	chassisPosition.z = MAFilterF32_Calc(mafilter_z, position_z);
}

void GetKeyboardCtrlChassisSpeed(void)
{
	/**************************************/
	/*            ___________             */
	/*           /___________\            */
	/*          /             \           */
	/*     ____/               \____      */
	/*                                    */
	/**************************************/
	uint8_t key = dbus.hc.key.val;
	float speed = (key & KEY_SHIFT) ? INPUT_CHASSIS_SPEED_MAX : INPUT_CHASSIS_SPEED_MAX / 2.f;
	float speed_x = (key & KEY_A) ? -speed : ((key & KEY_D) ? speed : 0);
	float speed_y = (key & KEY_S) ? -speed : ((key & KEY_W) ? speed : 0);
	float speed_z = 500*MAP(dbus.hc.mouse.x, MS_MIN, MS_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	if(mafilter_x == NULL) mafilter_x = MAFilterF32_Create(8);
	if(mafilter_y == NULL) mafilter_y = MAFilterF32_Create(8);
	if(mafilter_z == NULL) mafilter_z = MAFilterF32_Create(6);
	if(lastInputMode == INPUT_MODE_RC)
	{
		MAFilterF32_Reset(mafilter_x);
		MAFilterF32_Reset(mafilter_y);
		MAFilterF32_Reset(mafilter_z);
	}
	chassisSpeed.x = MAFilterF32_Calc(mafilter_x, speed_x);
	chassisSpeed.y = MAFilterF32_Calc(mafilter_y, speed_y);
	chassisSpeed.z = MAFilterF32_Calc(mafilter_z, speed_z);
}

void GetKeyboardCtrlChassisCurrent(void)
{
	/**************************************/
	/*            ___________             */
	/*           /___________\            */
	/*          /             \           */
	/*     ____/               \____      */
	/*                                    */
	/**************************************/
	uint8_t key = dbus.hc.key.val;
	float current = (key & KEY_SHIFT) ? INPUT_CHASSIS_CURRENT_MAX : INPUT_CHASSIS_CURRENT_MAX / 2.f;
	float current_x = (key & KEY_A) ? -current : ((key & KEY_D) ? current : 0);
	float current_y = (key & KEY_S) ? -current : ((key & KEY_W) ? current : 0);
	float current_z = 500*MAP(dbus.hc.mouse.x, MS_MIN, MS_MAX, -INPUT_GIMBALS_CURRENT_MAX, INPUT_GIMBALS_CURRENT_MAX);
	if(mafilter_x == NULL) mafilter_x = MAFilterF32_Create(8);
	if(mafilter_y == NULL) mafilter_y = MAFilterF32_Create(8);
	if(mafilter_z == NULL) mafilter_z = MAFilterF32_Create(6);
	if(lastInputMode == INPUT_MODE_RC)
	{
		MAFilterF32_Reset(mafilter_x);
		MAFilterF32_Reset(mafilter_y);
		MAFilterF32_Reset(mafilter_z);
	}
	chassisCurrent.x = MAFilterF32_Calc(mafilter_x, current_x);
	chassisCurrent.y = MAFilterF32_Calc(mafilter_y, current_y);
	chassisCurrent.z = MAFilterF32_Calc(mafilter_z, current_z);
}

void GetMouseCtrlGimbalsPosition(void)
{
	gimbalsPosition.yaw = MAP(dbus.hc.mouse.x, MS_MIN, MS_MAX, -INPUT_GIMBALS_POSITION_MAX, INPUT_GIMBALS_POSITION_MAX);
	gimbalsPosition.pit = MAP(dbus.hc.mouse.y, MS_MIN, MS_MAX, -INPUT_GIMBALS_POSITION_MAX, INPUT_GIMBALS_POSITION_MAX);
}

void GetMouseCtrlGimbalsSpeed(void)
{
	gimbalsSpeed.yaw = MAP(dbus.hc.mouse.x, MS_MIN, MS_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	gimbalsSpeed.pit = MAP(dbus.hc.mouse.y, MS_MIN, MS_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void GetMouseCtrlGimbalsCurrent(void)
{
	gimbalsCurrent.yaw = MAP(dbus.hc.mouse.x, MS_MIN, MS_MAX, -INPUT_GIMBALS_CURRENT_MAX, INPUT_GIMBALS_CURRENT_MAX);
	gimbalsCurrent.pit = MAP(dbus.hc.mouse.y, MS_MIN, MS_MAX, -INPUT_GIMBALS_CURRENT_MAX, INPUT_GIMBALS_CURRENT_MAX);
}

void InputTask(void)
{
	GetInputMode();
	GetCtrlMode();
	if(inputMode == INPUT_MODE_RC)
	{
		GetSwitchPanel();
		switch(ctrlMode)
		{
			case CTRL_MODE_POSITION:
			{
				GetStickCtrlChassisPosition();
				GetStickCtrlGimbalsPosition();
			}break;
			case CTRL_MODE_SPEED:
			{
				GetStickCtrlChassisSpeed();
				GetStickCtrlGimbalsSpeed();
			}break;
			case CTRL_MODE_CURRENT:
			{
				GetStickCtrlChassisCurrent();
				GetStickCtrlGimbalsCurrent();
			}break;
			default:
			{
				GetStickCtrlChassisSpeed();
				GetStickCtrlGimbalsSpeed();
			}break;
		}
		
	}
	else if(inputMode == INPUT_MODE_HC)
	{
		GetKeyboard();
		switch(ctrlMode)
		{
			case CTRL_MODE_POSITION:
			{
				GetKeyboardCtrlChassisPosition();
				GetMouseCtrlGimbalsPosition();
			}break;
			case CTRL_MODE_SPEED:
			{
				GetKeyboardCtrlChassisSpeed();
				GetMouseCtrlGimbalsSpeed();
			}break;
			case CTRL_MODE_CURRENT:
			{
				GetKeyboardCtrlChassisCurrent();
				GetMouseCtrlGimbalsCurrent();
			}break;
			default:
			{
			}break;
		}
		
	}
}
