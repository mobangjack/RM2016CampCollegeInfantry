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
 
#ifndef __QUAD_ENCODER_H__
#define __QUAD_ENCODER_H__

#define QUAD_ENCODER_DIR 1
#define QUAD_ENCODER_OFFSET 0x7fff
#define QUAD_ENCODER_CNT() (QUAD_ENCODER_DIR?(TIM3->CNT-QUAD_ENCODER_OFFSET):(QUAD_ENCODER_OFFSET-TIM3->CNT))
#define QUAD_ENCODER_START() (TIM3->CNT = QUAD_ENCODER_OFFSET)

void QuadEncoder_Config(void);

#endif
