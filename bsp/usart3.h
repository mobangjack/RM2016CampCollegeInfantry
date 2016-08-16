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
 
#ifndef __USART3_H__
#define __USART3_H__

#include <stdint.h>

#define USART3_TX_FIFO_SIZE 256u

void USART3_Config(void);

void USART3_Print(uint8_t ch);
void USART3_PrintString(const char* str);
void USART3_PrintBlock(uint8_t* pdata, uint8_t len);

extern uint8_t usart3_rx_data;

#endif
