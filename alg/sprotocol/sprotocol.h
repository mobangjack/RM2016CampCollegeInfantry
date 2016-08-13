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

#ifndef __SPROTOCOL_H__
#define __SPROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************/
/*                       Dependencies                             */
/******************************************************************/
#include <stdint.h>
#include <string.h>
#include "crc16.h"

/******************************************************************/
/*                   Top Level Negotiation                        */
/******************************************************************/
typedef struct
{
	uint8_t m_header;
	uint16_t m_version;
	uint16_t m_token;
}SProtocol;

/******************************************************************/
/*                 Protocol Header Structure                      */
/******************************************************************/
#pragma pack(1)
typedef struct
{
	uint8_t m_header;
	uint16_t m_version;
	uint16_t m_msg_len;
	uint8_t m_msg_type;
	uint8_t m_session_id;
	uint32_t m_seq_num;
}SProtocolHeader;

/******************************************************************/
/*                     Protocol RX FIFO                           */
/******************************************************************/
#define SPROTOCOL_STACK_BUF_SIZE 1024u
typedef struct
{
	uint8_t buf[SPROTOCOL_STACK_BUF_SIZE];
	uint32_t r;
	uint32_t w;
}SProtocolFifo;


/******************************************************************/
/*                        Format Msg                              */
/******************************************************************/
SProtocolHeader* SProtocol_Format(SProtocol* sprotocol, uint8_t* src_buf, uint32_t src_len, uint8_t* dst_buf, uint8_t msg_type, uint8_t session_id, uint32_t seq_num);

/******************************************************************/
/*                        Verify Msg                              */
/******************************************************************/
uint8_t SProtocol_Verify(SProtocol* sprotocol, uint8_t* msg_buf);

/******************************************************************/
/*            Push a Element to the SProtocol FIFO                */
/******************************************************************/
uint8_t SProtocol_Push(SProtocolFifo* sprotocol_fifo, uint8_t word);

/******************************************************************/
/*            Push Elements to the SProtocol FIFO                 */
/******************************************************************/
uint8_t SProtocol_PushBlock(SProtocolFifo* sprotocol_fifo, uint8_t* block, uint32_t len);

/******************************************************************/
/*            Pop Data Out From the SProtocol FIFO                */
/******************************************************************/
SProtocolHeader* SProtocol_Pop(SProtocol* sprotocol, SProtocolFifo* sprotocol_fifo, uint8_t* data, uint32_t* len);

/******************************************************************/
/*            Get Used Space of the SProtocol FIFO                */
/******************************************************************/
uint32_t SProtocol_GetFifoUsedSpace(SProtocolFifo* sprotocol_fifo);

/******************************************************************/
/*            Get Free Space of the SProtocol FIFO                */
/******************************************************************/
uint32_t SProtocol_GetFifoFreeSpace(SProtocolFifo* sprotocol_fifo);

/******************************************************************/
/*            Get Read Address of the SProtocol FIFO              */
/******************************************************************/
uint8_t* SProtocol_GetFifoReadAddr(SProtocolFifo* sprotocol_fifo);

/******************************************************************/
/*            Get Write Address of the SProtocol FIFO             */
/******************************************************************/
uint8_t* SProtocol_GetFifoWriteAddr(SProtocolFifo* sprotocol_fifo);

#ifdef __cplusplus
}
#endif

#endif

