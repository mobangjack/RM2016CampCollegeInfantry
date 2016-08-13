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
 
#ifndef __MECANUM_H__
#define __MECANUM_H__

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

#define MECANUM_A 0.160f  //Mecanum wheel span
#define MECANUM_B 0.160f  //Mecanum wheel base
//#define MECANUM_L 0.226f  //MECANUM_L = SQRT(A^2+B^2)
#define MECANUM_L 0.3272f   //MECANUM_L = SQRT(A^2+B^2) -> Modified value, to correct Z axis data
#define MECANUM_R 0.076f  //Mecanum wheel radius

typedef struct
{
	float x;
	float y;
	float z;
	float w1;
	float w2;
	float w3;
	float w4;
}Mecanum;

void Mecanum_Synthesis(Mecanum* mecanum);
void Mecanum_Decompose(Mecanum* mecanum);

#endif
