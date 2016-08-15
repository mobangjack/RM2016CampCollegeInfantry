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

void DebugIMU(void)
{
	printf("ax=%f,ay=%f,az=%f,gx=%f,gy=%f,gz=%f\n", MPU6050_Real_Data.Accel_X, MPU6050_Real_Data.Accel_Y, MPU6050_Real_Data.Accel_Z, MPU6050_Real_Data.Gyro_X, MPU6050_Real_Data.Gyro_Y, MPU6050_Real_Data.Gyro_Z);
}

int main(void)
{
	uint32_t t = 0;
	BSP_Config();
	delay_ms(500);
	MPU6050_Initialize();
	MPU6050_IntConfiguration();     
	MPU6050_EnableInt();
	Init_Quaternion();
	while(1)
	{
		IMU_getYawPitchRoll(angle);
		if(Micros() % 10000 == 0)
		{
			
			//OdomTask();
			//printf("%f\n",ZGyroAngle);
		}
		if(Micros() % 20000 == 0)
		{
			DebugIMU();
		}
		if(Micros() % 1000000 == 0)
		{
			t++;
			printf("%d\n",t);
		}
    }
}
