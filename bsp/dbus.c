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
 
#include "dbus.h"

/***************************RC*******************************/
void RC_ENC(RC* rc, uint8_t* buf)
{
	buf[0] = rc->ch0&0xff;
	buf[1] = (rc->ch1<<3) | (rc->ch0>>8);
	buf[2] = (rc->ch2<<6) | (rc->ch1>>5);
	buf[3] = rc->ch2;
	buf[4] = (rc->ch3<<1) | (rc->ch2>>10);
	buf[5] = (rc->s2<<6) | (rc->s1<<4) | (rc->ch3>>7);
}

void RC_DEC(RC* rc, uint8_t* buf)
{
	rc->ch0 = (buf[0] | (buf[1] << 8)) & 0x07ff;          //!< Channel 0  
	rc->ch1 = ((buf[1] >> 3) | (buf[2] << 5)) & 0x07ff;   //!< Channel 1         
	rc->ch2 = ((buf[2] >> 6) | (buf[3] << 2) |            //!< Channel 2                          
		(buf[4] << 10)) & 0x07ff;
	rc->ch3 = ((buf[4] >> 1) | (buf[5] << 7)) & 0x07ff;   //!< Channel 3   
	rc->s1 = ((buf[5] >> 4) & 0x000c) >> 2;                      //!< Switch left         
	rc->s2 = ((buf[5] >> 4) & 0x0003);                           //!< Switch right  
}

/***************************HC*******************************/
void HC_ENC(HC* hc, uint8_t* buf)
{
	buf[0] = hc->mouse.x;
	buf[1] = hc->mouse.x>>8;
	buf[2] = hc->mouse.y;
	buf[3] = hc->mouse.y>>8;
	buf[4] = hc->mouse.z;
	buf[5] = hc->mouse.z>>8;
	buf[6] = hc->mouse.l;
	buf[7] = hc->mouse.r;
	buf[8] = hc->key.val;
	buf[9] = hc->key.val>>8;
	buf[10] = hc->res.val;
	buf[11] = hc->res.val>>8;
}
void HC_DEC(HC* hc, uint8_t* buf)
{
	hc->mouse.x = buf[0] | (buf[1] << 8);     //!< Mouse X axis 
	hc->mouse.y = buf[2] | (buf[3] << 8);     //!< Mouse Y axis 
	hc->mouse.z = buf[4] | (buf[5] << 8);     //!< Mouse Z axis 
	hc->mouse.l = buf[6];                     //!< Mouse Left Is Press ?
	hc->mouse.r = buf[7];                     //!< Mouse Right Is Press ? 
	hc->key.val = buf[8] | (buf[9] << 8);     //!< KeyBoard value   
	hc->res.val = buf[10] | (buf[11] << 8);   //!< Reserve 
}

/***************************DBUS*******************************/
void DBUS_ENC(DBUS* dbus, uint8_t* buf)
{
	RC_ENC(&dbus->rc, buf);
	HC_ENC(&dbus->hc, buf+6);
}

void DBUS_DEC(DBUS* dbus, uint8_t* buf)
{
	RC_DEC(&dbus->rc, buf);
	HC_DEC(&dbus->hc, buf+6);
}

