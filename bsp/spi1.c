#include "main.h"

//串行外设接口SPI的初始化，SPI配置成主模式							  
//本例程选用SPI1对NRF24L01进行读写操作，先对SPI1进行初始化
void SPI1_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable SPI1 and GPIO clocks */
  RCC_AHB1PeriphClockCmd(RCC_SPI1, ENABLE);

  /*!< SPI Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_SPI1_CLK, ENABLE);

  GPIO_PinAFConfig(SPI1_GPIO_PORT, SPI1_SCK_SOURCE, GPIO_AF_SPI1);
  GPIO_PinAFConfig(SPI1_GPIO_PORT, SPI1_MISO_SOURCE, GPIO_AF_SPI1);
  GPIO_PinAFConfig(SPI1_GPIO_PORT, SPI1_MOSI_SOURCE, GPIO_AF_SPI1);
      
  /*!< Configure  pins: SCK */
  GPIO_InitStructure.GPIO_Pin = SPI1_SCK;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
  GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure  pins: MISO */
  GPIO_InitStructure.GPIO_Pin = SPI1_MISO;
  GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure  pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = SPI1_MOSI;
  GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStructure);

  /* SPI1 configuration *///初始化SPI1结构体
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI1设置为两线全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //设置SPI1为主模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //SPI发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //串行时钟在不操作时，时钟为低电平
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //第一个时钟沿开始采样数据
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS信号由软件（使用SSI位）管理
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //SPI波特率预分频值为8
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输从MSB位开始
  SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC值计算的多项式
  SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPI1寄存器
  
  /* Enable SPI1  *///使能SPI1外设
  SPI_Cmd(SPI1, ENABLE);
    
  SPI1_ReadWriteByte(0xff);                        //启动传输	
}
	

u8 SPI1_ReadWriteByte(u8 TxData)                                        //SPI读写数据函数
{		
	u8 retry = 0;				 	
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)      //发送缓存标志位为空
	{
		retry++;
		if(retry > 200) return 0;
	}			  
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI1, TxData);                                    //通过外设SPI1发送一个数据
	retry = 0;
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)   //接收缓存标志位不为空
	{
		retry++;
		if(retry > 200) return 0;
	}	  						    
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI1);                                 //通过SPI1返回接收数据				    
}






















