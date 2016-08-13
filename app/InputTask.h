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
 
#ifndef __INPUT_TASK_H__
#define __INPUT_TASK_H__

#include <stdint.h>

#define INPUT_CHASSIS_POSITION_MAX 4.0f     //max position: 4m
#define INPUT_CHASSIS_SPEED_MAX    4.0f        //max speed:    4m/s
#define INPUT_CHASSIS_CURRENT_MAX  400.0f      //max current:  4A

#define INPUT_GIMBALS_POSITION_MAX 3.1415926f     //max position: 4m
#define INPUT_GIMBALS_SPEED_MAX    3.1415926f        //max speed: 4m/s
#define INPUT_GIMBALS_CURRENT_MAX  400.0f      //max current:  4A

#define GET_SWITCH_ACTION(lastState,thisState) (((lastState)<<2)|(thisState))
#define SWITCH_ACTION_3TO1 GET_SWITCH_ACTION(3, 1)
#define SWITCH_ACTION_1TO3 GET_SWITCH_ACTION(1, 3)
#define SWITCH_ACTION_3TO2 GET_SWITCH_ACTION(3, 2)
#define SWITCH_ACTION_2TO3 GET_SWITCH_ACTION(2, 3)
#define SWITCH_ACTION_NONE 0

#define GET_KEY_ACTION(lastState,thisState) (((lastState)<<1)|(thisState))
#define KEY_ACTION_UP GET_KEY_ACTION(KEY_DN, KEY_UP)
#define KEY_ACTION_DN GET_KEY_ACTION(KEY_UP, KEY_DN)

/*******************************************/
/* Mecanum Wheel Power Transmission System */
/*******************************************/
/*              2        1                 */
/*                 y|                      */
/*                  |___                   */
/*                z    x                   */
/*              3        4                 */
/*                                         */
/*******************************************/
typedef enum
{
	ON = 1,
	OFF = 0,
}SwitchingValue;

typedef enum
{
	INPUT_MODE_RC = 0x03,
	INPUT_MODE_HC = 0x01,
	INPUT_MODE_NO = 0x02,
}InputMode;

typedef enum
{
	CTRL_MODE_POSITION = 0x00,
	CTRL_MODE_SPEED = 0x01,
	CTRL_MODE_CURRENT = 0x02,
}CtrlMode;

typedef struct
{
	float x;
	float y;
	float z;
}ChassisPosition;

typedef struct
{
	float x;
	float y;
	float z;
}ChassisSpeed;

typedef struct
{
	float x;
	float y;
	float z;
}ChassisCurrent;

typedef struct
{
	float yaw;
	float pit;
}GimbalsPosition;

typedef struct
{
	float yaw;
	float pit;
}GimbalsSpeed;

typedef struct
{
	float yaw;
	float pit;
}GimbalsCurrent;

typedef struct
{
	uint8_t thisState;
	uint8_t lastState;
	uint8_t action;
}SwitchState;

typedef struct
{
	uint8_t thisState;
	uint8_t lastState;
	uint8_t action;
}KeyState;

typedef struct
{
	SwitchState s1;
	SwitchState s2;
}SwitchPanel;

typedef struct
{
	KeyState A;
	KeyState D;
	KeyState W;
	KeyState S;
	KeyState Shift;
	KeyState Ctrl;
	KeyState Q;
	KeyState E;
}Keyboard;

void InputTask(void);

extern InputMode inputMode;
extern CtrlMode ctrlMode;
extern CtrlMode lastCtrlMode;
extern SwitchPanel switchPanel;
extern Keyboard keyboard;
extern ChassisPosition chassisPosition;
extern ChassisSpeed chassisSpeed;
extern ChassisCurrent chassisCurrent;
extern GimbalsPosition gimbalsPosition;
extern GimbalsSpeed gimbalsSpeed;
extern GimbalsCurrent gimbalsCurrent;

#endif
