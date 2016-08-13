#SProtocol： 通用串行包传输协议
---
###协议格式：帧头 | 数据 | 校验
###帧头：一字节的起始标志，两字节的版本号，两字节的消息长度，一字节的消息类型，一字节的session_id,四字节的消息序列号。
	typedef struct
	{
		uint8_t m_header;		//一字节的起始标志
		uint16_t m_version;		//两字节的版本号
		uint16_t m_msg_len;		//两字节的消息长度
		uint8_t m_msg_type;		//一字节的消息类型
		uint8_t m_session_id;	//一字节的session_id
		uint32_t m_seq_num;		//四字节的消息序列号
	}SProtocolHeader;

###数据：原始的数据块
###校验：CRC16校验和

###应用示例：
	#include "sprotocol.h"
	
	#define MY_SPROTOCOL \
	{ \
		.header = 0xaa,
		.version = 0x0001,
		.token = 0x1234,
	} \
	
	#define MSG_TYPE_IMU 0x01
	
	#define DATA_LEN 16
	#define MSG_BUF_LEN 100
	
	SProtocol sprotocol = MY_SPROTOCOL;
	SProtocolFifo sprotocol_fifo;
	
	uint8_t data[DATA_LEN] = {0};
	uint8_t msg_buf[MSG_BUF_LEN] = {0];
	
	void TX(void)
	{
		static const SESSION_ID = 0xff;
		static uint32_t seq_num = 0;
		SProtocolHeader* sprotocol_header = SProtocol_Format(&sprotocol, data, DATA_LEN, msg_buf, MSG_TYPE_IMU, SESSION_ID, seq_num++);
		USART3_PrintBlock(dst, sprotocol_header->m_msg_len);
	}
	
	void RX(void)
	{
		uin32_t len = USART3_Read(buf, DST_LEN);
		SProtocol_PushBlock(&sprotocol_fifo, buf, len);
		while(SProtocol_Pop(&sprotocol, &sprotocol_fifo, data, &len)
		{
			//Do something with the data
		}
	}
