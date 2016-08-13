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
 
#include "fifo.h"

FIFO* FIFO_Create(uint32_t len)
{
	FIFO* fifo = (FIFO*)malloc(sizeof(FIFO));
	if(fifo == NULL) return NULL;
	fifo->buf = (uint8_t*)malloc(len);
	if(fifo->buf == NULL)
	{
		free(fifo);
		fifo = NULL;
		return NULL;
	}
	fifo->len = len;
	fifo->r = 0;
	fifo->w = 0;
	return fifo;
}

void FIFO_Init(FIFO* fifo, uint8_t* buf, uint32_t len)
{
	fifo->buf = buf;
	fifo->len = len;
	fifo->r = 0;
	fifo->w = 0;
}

void FIFO_Flush(FIFO* fifo)
{
	fifo->r = 0;
	fifo->w = 0;
}

uint8_t FIFO_Push(FIFO* fifo, uint8_t element)
{
	if(fifo->w == fifo->len)
	{
		if(fifo->r == 0)
		{
			return 0;
		}
		else
		{
			uint32_t i = fifo->r;
			for(; i < fifo->len; i++)
			{
				fifo->buf[i-fifo->r] = fifo->buf[i];
			}
			fifo->w-= fifo->r;
			fifo->r = 0;
		}
	}
	fifo->buf[fifo->w++] = element;
	return 1;
}

uint8_t FIFO_PushBlock(FIFO* fifo, uint8_t* block, uint32_t size)
{
	uint32_t i = 0;
	for(i = 0; i < size; i++)
	{
		if(!FIFO_Push(fifo,block[i]))
			return 0;
	}
	return 1;
}

uint8_t FIFO_Pop(FIFO* fifo, uint8_t* element)
{
	if(FIFO_IsEmpty(fifo))
	{
		return 0;
	}
	*element = fifo->buf[fifo->r++];
	return 1;
}

uint8_t FIFO_PopBlock(FIFO* fifo, uint8_t* block, uint32_t size)
{
	uint32_t i = 0;
	if(FIFO_GetUsedSpace(fifo) < size)
	{
		return 0;
	}
	for(i = 0; i < size; i++)
	{
		FIFO_Pop(fifo,&block[i]);
	}
	return 1;
}

uint8_t FIFO_Preread(FIFO* fifo, uint8_t* element, uint32_t offset)
{
	uint32_t i = fifo->r + offset;
	if(i >= fifo->w)
	{
		return 0;
	}
	*element = fifo->buf[i];
	return 1;
}

uint8_t FIFO_PrereadBlock(FIFO* fifo, uint8_t* block, uint32_t size, uint32_t offset)
{
	uint32_t i = 0;
	if(fifo->r + offset + size >= fifo->w)
	{
		return 0;
	}
	for(i = fifo->r + offset; i < fifo->r + offset + size; i++)
	{
		FIFO_Preread(fifo,&block[i],i);
	}
	return 1;
}

uint8_t FIFO_IsFull(FIFO* fifo)
{
	return fifo->r == 0 && fifo->w == fifo->len;
}

uint8_t FIFO_IsEmpty(FIFO* fifo)
{
	return fifo->r == fifo->w;
}

uint32_t FIFO_GetUsedSpace(FIFO* fifo)
{
	return fifo->w - fifo->r;
}

uint32_t FIFO_GetFreeSpace(FIFO* fifo)
{
	return fifo->len - fifo->w + fifo->r;
}

void FIFO_Destroy(FIFO* fifo)
{
	free(fifo);
	fifo = NULL;
}

