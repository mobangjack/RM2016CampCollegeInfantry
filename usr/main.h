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
 
#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

//alg
#include "pid.h"
#include "ramp.h"
#include "fifo.h"
#include "crc16.h"
#include "mecanum.h"
#include "sprotocol.h"
#include "mafilter_i16.h"
#include "mafilter_f32.h"


//bsp
#include "bsp.h"
#include "can1.h"
#include "can2.h"
#include "dbus.h"
#include "delay.h"
#include "encoder.h"
#include "led.h"
#include "motor.h"
#include "pwm.h"
#include "QuadEncoder.h"
#include "timer.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "zgyro.h"

//imu
#include "imu.h"
#include "mpu6050_driver.h"
#include "mpu6050_i2c.h"
#include "mpu6050_interrupt.h"

//nrf
#include "spi1.h"
#include "NRF24L01.h"

//app
#include "Can1Task.h"
#include "Can2Task.h"
#include "InputTask.h"
#include "ControlTask.h"
#include "NRFTask.h"
#include "OdomTask.h"

//common definition
#define PI 3.1415926f
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)

#endif 
