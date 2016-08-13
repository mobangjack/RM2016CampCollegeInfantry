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
 
#ifndef __DBUS_H__
#define __DBUS_H__

#include <stdint.h>

/* ----------------------- RC Channel Value Definition---------------------------- */
#define CH_MIN              	 ((uint16_t)364   ) 
#define CH_MID           	 	 ((uint16_t)1024  ) 
#define CH_MAX              	 ((uint16_t)1684  )  
#define CH_OFF              	 ((uint16_t)660   )  
/* ----------------------- RC Switch Value Definition----------------------------- */
#define SW_UP                    ((uint8_t)1      ) 
#define SW_MD                    ((uint8_t)3      ) 
#define SW_DN                    ((uint8_t)2      )  
/* ----------------------- PC Mouse Value Definition-------------------------------- */
#define MS_MIN            		 ((int16_t)-32768 ) 
#define MS_MID                   ((int16_t)0      ) 
#define MS_MAX		             ((int16_t)32767  ) 
#define MS_UP         		     ((uint8_t)0      ) 
#define MS_DN         		     ((uint8_t)1      ) 
/* ----------------------- PC Key Value Definition-------------------------------- */
#define KEY_UP                   ((uint8_t)0x00   )
#define KEY_DN                   ((uint8_t)0x01   )
#define KEY_W         			 ((uint8_t)0x01<<0) 
#define KEY_S         			 ((uint8_t)0x01<<1) 
#define KEY_A         			 ((uint8_t)0x01<<2) 
#define KEY_D         			 ((uint8_t)0x01<<3)
#define KEY_SHIFT     		     ((uint8_t)0x01<<4) 
#define KEY_CTRL      		     ((uint8_t)0x01<<5)
#define KEY_Q         		     ((uint8_t)0x01<<6) 
#define KEY_E         			 ((uint8_t)0x01<<7)

typedef struct RC
{
	uint16_t ch0;
	uint16_t ch1;
	uint16_t ch2;
	uint16_t ch3;
	uint8_t  s1;
	uint8_t  s2;
}RC; // remote control

typedef struct Mouse
{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t  l;
	uint8_t  r;
}Mouse; // mouse control

typedef struct Key
{
	uint16_t val : 16;
}Key; // key control

typedef struct Res
{
	uint16_t val;
}Res; // reserve control bits

typedef struct
{
	Mouse mouse;
	Key key;
	Res res;
}HC; // Host Control

typedef struct
{
	RC rc;
	HC hc;
}DBUS; // Robomasters DT7 Receiver DBUS Protocol

void RC_ENC(RC* rc, uint8_t* buf);
void RC_DEC(RC* rc, uint8_t* buf);

void HC_ENC(HC* hc, uint8_t* buf);
void HC_DEC(HC* hc, uint8_t* buf);

void DBUS_ENC(DBUS* dbus, uint8_t* buf);
void DBUS_DEC(DBUS* dbus, uint8_t* buf);

#endif
