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
 
#ifndef __FIFO_H__
#define __FIFO_H__

#ifdef __cpluplus
extern "C" {
#endif
	
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
	
typedef struct FIFO
{
	uint8_t* buf;
	uint32_t len;
	uint32_t r;
	uint32_t w;
}FIFO;

FIFO* FIFO_Create(uint32_t len);
void FIFO_Init(FIFO* fifo, uint8_t* buf, uint32_t len);
void FIFO_Flush(FIFO* fifo);
uint8_t FIFO_Push(FIFO* fifo, uint8_t element);
uint8_t FIFO_PushBlock(FIFO* fifo, uint8_t* block, uint32_t size);
uint8_t FIFO_Pop(FIFO* fifo, uint8_t* element);
uint8_t FIFO_PopBlock(FIFO* fifo, uint8_t* block, uint32_t size);
uint8_t FIFO_Preread(FIFO* fifo, uint8_t* element, uint32_t offset);
uint8_t FIFO_PrereadBlock(FIFO* fifo, uint8_t* block, uint32_t size, uint32_t offset);
uint8_t FIFO_IsFull(FIFO* fifo);
uint8_t FIFO_IsEmpty(FIFO* fifo);
uint32_t FIFO_GetUsedSpace(FIFO* fifo);
uint32_t FIFO_GetFreeSpace(FIFO* fifo);
void FIFO_Destroy(FIFO* fifo);

#ifdef __cpluplus
}
#endif
	
#endif
