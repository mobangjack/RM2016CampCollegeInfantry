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
 
#include "mecanum.h"

/*******************************************/
/* Mecanum Wheel Power Transmission System */
/*******************************************/
/*              2        1                 */
/*                  |y                     */
/*                 b|___x                  */
/*               z    a                    */
/*              3        4                 */
/*                                         */
/*******************************************/

void Mecanum_Synthesis(Mecanum* mecanum)
{
	mecanum->x = ( mecanum->w1 + mecanum->w2 - mecanum->w3 - mecanum->w4) * MECANUM_R / 4.f;
	mecanum->y = (-mecanum->w1 + mecanum->w2 + mecanum->w3 - mecanum->w4) * MECANUM_R / 4.f;
	mecanum->z = ( mecanum->w1 + mecanum->w2 + mecanum->w3 + mecanum->w4) * MECANUM_R / 4.f / MECANUM_L;
}

void Mecanum_Decompose(Mecanum* mecanum)
{
	mecanum->w1 = ( mecanum->x - mecanum->y + mecanum->z * MECANUM_L) / MECANUM_R;
	mecanum->w2 = ( mecanum->x + mecanum->y + mecanum->z * MECANUM_L) / MECANUM_R;
	mecanum->w3 = (-mecanum->x + mecanum->y + mecanum->z * MECANUM_L) / MECANUM_R;
	mecanum->w4 = (-mecanum->x - mecanum->y + mecanum->z * MECANUM_L) / MECANUM_R;
}
