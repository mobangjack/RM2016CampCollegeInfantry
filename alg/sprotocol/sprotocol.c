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
 
/******************************************************************/
/*       Uniform Serial Packet Transportation Protocol            */
/******************************************************************/

#include "sprotocol.h"

/******************************************************************/
/*                        Format Msg                              */
/******************************************************************/
SProtocolHeader* SProtocol_Format(SProtocol* sprotocol, uint8_t* src_buf, uint32_t src_len, uint8_t* dst_buf, uint8_t msg_type, uint8_t session_id, uint32_t seq_num)
{
	SProtocolHeader* sprotocol_header = (SProtocolHeader*)dst_buf;
	sprotocol_header->m_header = sprotocol->m_header;
	sprotocol_header->m_version = sprotocol->m_version;
	sprotocol_header->m_msg_len = src_len + sizeof(SProtocolHeader) + 2; //crc16: 2 bytes
	sprotocol_header->m_msg_type = msg_type;
	sprotocol_header->m_session_id = session_id;
	sprotocol_header->m_seq_num = seq_num;
	memcpy(dst_buf+sizeof(SProtocolHeader), src_buf, src_len);
	CRC16Append(dst_buf, sprotocol_header->m_msg_len, sprotocol->m_token);
	return sprotocol_header;
}

/******************************************************************/
/*                        Verify Msg                              */
/******************************************************************/
uint8_t SProtocol_Verify(SProtocol* sprotocol, uint8_t* msg_buf)
{
	SProtocolHeader* sprotocol_header = (SProtocolHeader*)msg_buf;
	if(sprotocol_header->m_header != sprotocol->m_header) return 0;
	if(sprotocol_header->m_version != sprotocol->m_version) return 0;
	if(!CRC16Check(msg_buf, sprotocol_header->m_msg_len, sprotocol->m_token)) return 0;
	return 1;
}

/******************************************************************/
/*            Push a Element to the SProtocol FIFO                */
/******************************************************************/
uint8_t SProtocol_Push(SProtocolFifo* sprotocol_fifo, uint8_t word)
{
	uint32_t i = 0;
	if(sprotocol_fifo->w == SPROTOCOL_STACK_BUF_SIZE)
	{
		if(sprotocol_fifo->r == 0) return 0;
		for(i = sprotocol_fifo->r; i < SPROTOCOL_STACK_BUF_SIZE; i++)
		{
			sprotocol_fifo->buf[i-sprotocol_fifo->r] = sprotocol_fifo->buf[i];
		}
		sprotocol_fifo->w -= sprotocol_fifo->r;
		sprotocol_fifo->r = 0;
	}
	sprotocol_fifo->buf[sprotocol_fifo->w++] = word;
	return 1;
}

/******************************************************************/
/*            Push Elements to the SProtocol FIFO                 */
/******************************************************************/
uint8_t SProtocol_PushBlock(SProtocolFifo* sprotocol_fifo, uint8_t* block, uint32_t len)
{
	uint32_t i = 0;
	for(i = 0; i < len; i++)
	{
		if(!SProtocol_Push(sprotocol_fifo, block[i]))
		{
			return 0;
		}
	}
	return 1;
}

/******************************************************************/
/*            Pop Data Out From the SProtocol FIFO                */
/******************************************************************/
SProtocolHeader* SProtocol_Pop(SProtocol* sprotocol, SProtocolFifo* sprotocol_fifo, uint8_t* data, uint32_t* len)
{
	if(SProtocol_GetFifoUsedSpace(sprotocol_fifo) < sizeof(SProtocolHeader)) return NULL;
	SProtocolHeader* sprotocol_header = (SProtocolHeader*)(sprotocol_fifo->buf+sprotocol_fifo->r);
	if(!SProtocol_Verify(sprotocol, sprotocol_fifo->buf+sprotocol_fifo->r)) return NULL;
	if(SProtocol_GetFifoUsedSpace(sprotocol_fifo) < sprotocol_header->m_msg_len) return NULL;
	*len = sprotocol_header->m_msg_len - sizeof(SProtocolHeader) - 2;
	memcpy(data, sprotocol_fifo->buf+sprotocol_fifo->r+sizeof(SProtocolHeader), *len);
	sprotocol_fifo->r += sprotocol_header->m_msg_len;
	return sprotocol_header;
}

/******************************************************************/
/*            Get Used Space of the SProtocol FIFO                */
/******************************************************************/
uint32_t SProtocol_GetFifoUsedSpace(SProtocolFifo* sprotocol_fifo)
{
	return sprotocol_fifo->w - sprotocol_fifo->r;
}

/******************************************************************/
/*            Get Free Space of the SProtocol FIFO                */
/******************************************************************/
uint32_t SProtocol_GetFifoFreeSpace(SProtocolFifo* sprotocol_fifo)
{
	return SPROTOCOL_STACK_BUF_SIZE-SProtocol_GetFifoUsedSpace(sprotocol_fifo);
}

/******************************************************************/
/*            Get Read Address of the SProtocol FIFO              */
/******************************************************************/
uint8_t* SProtocol_GetFifoReadAddr(SProtocolFifo* sprotocol_fifo)
{
	return sprotocol_fifo->buf+sprotocol_fifo->r;
}

/******************************************************************/
/*            Get Write Address of the SProtocol FIFO             */
/******************************************************************/
uint8_t* SProtocol_GetFifoWriteAddr(SProtocolFifo* sprotocol_fifo)
{
	return sprotocol_fifo->buf+sprotocol_fifo->w;
}

