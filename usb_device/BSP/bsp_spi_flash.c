#include "bsp_spi_flash.h"

/*以下部分针对SPI底层初始化。包括端口、SPI等*/


/**
 * @brief 初始化SPI用到的引脚等。
 */
void sFLASH_LowLevel_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

		GPIO_InitStruct(&GPIO_InitStructure);
	
    /*!< sFLASH_SPI_CS_GPIO, sFLASH_SPI_MOSI_GPIO, sFLASH_SPI_MISO_GPIO
         and sFLASH_SPI_SCK_GPIO Periph clock enable */
    RCC_EnableAHB1PeriphClk(
        sFLASH_CS_GPIO_CLK | sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK | sFLASH_SPI_SCK_GPIO_CLK, ENABLE);

    /*!< sFLASH_SPI Periph clock enable */
    RCC_EnableAPB2PeriphClk(sFLASH_SPI_CLK, ENABLE);

    /*!< Configure sFLASH_SPI pins: SCK */
    GPIO_InitStructure.Pin        = sFLASH_SPI_SCK_PIN;
		GPIO_InitStructure.GPIO_Pull  = GPIO_NO_PULL;
		GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_SCK_GPIO_AF;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MOSI */
    GPIO_InitStructure.Pin = sFLASH_SPI_MOSI_PIN;
		GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
		GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_MOSI_GPIO_AF;
    GPIO_InitPeripheral(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MISO */
    GPIO_InitStructure.Pin       = sFLASH_SPI_MISO_PIN;
		GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
		GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_MISO_GPIO_AF;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
    GPIO_InitStructure.Pin       = sFLASH_CS_PIN;
		GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
		GPIO_InitStructure.GPIO_Alternate = sFLASH_CS_GPIO_AF;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}


/**
*\*\name    DMA_Flash_Init.
*\*\fun     FLASH DMA INIT.
*\*\param   none
*\*\return  none 
**/
void DMA_Flash_Init()
{
    DMA_InitType DMA_InitStructure;

    /*ENABLE DMA CLK*/
    RCC_EnableAHBPeriphClk(sFLASH_SPI_DMA_CLK, ENABLE);

    /* SPI_FLASH_Rx_DMA_Channel configuration ---------------------------------------------*/
    DMA_DeInit(sFLASH_SPI_Rx_DMA_Channel);
		DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&sFLASH_SPI->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)0;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = sFLASH_SPI_ONE_PAGE;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.MemoryInc 		 = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_BYTE;
    DMA_InitStructure.MemDataSize    = DMA_MEM_DATA_WIDTH_BYTE;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(sFLASH_SPI_Rx_DMA_Channel, &DMA_InitStructure);
		DMA_RequestRemap(sFLASH_SPI_Rx_DMA_Remap,sFLASH_SPI_Rx_DMA_Channel,ENABLE);
	
    /* SPI_FLASH_Tx_DMA_Channel configuration ---------------------------------------------*/
    DMA_DeInit(sFLASH_SPI_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = (uint32_t)&sFLASH_SPI->DAT;
    DMA_InitStructure.MemAddr    = (uint32_t)0;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.Priority   = DMA_PRIORITY_HIGH;
    DMA_Init(sFLASH_SPI_Tx_DMA_Channel, &DMA_InitStructure);
		DMA_RequestRemap(sFLASH_SPI_Tx_DMA_Remap,sFLASH_SPI_Tx_DMA_Channel,ENABLE);		
}

/**
 * @brief  取消SPI闪存驱动器使用的外围设备的初始化。
 */
void sFLASH_LowLevel_DeInit(void)
{
    GPIO_InitType GPIO_InitStructure;

		GPIO_InitStruct(&GPIO_InitStructure);
    /*!< Disable the sFLASH_SPI  */
    SPI_Enable(sFLASH_SPI, DISABLE);

    /*!< DeInitializes the sFLASH_SPI */
    SPI_I2S_DeInit(sFLASH_SPI);

    /*!< sFLASH_SPI Periph clock disable */
    RCC_EnableAPB2PeriphClk(sFLASH_SPI_CLK, DISABLE);

    /*!< Configure sFLASH_SPI pins: SCK */
    GPIO_InitStructure.Pin       = sFLASH_SPI_SCK_PIN;
		GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
		GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_SCK_GPIO_AF;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MISO */
    GPIO_InitStructure.Pin = sFLASH_SPI_MISO_PIN;
		GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
		GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_MISO_GPIO_AF;
    GPIO_InitPeripheral(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MOSI */
    GPIO_InitStructure.Pin = sFLASH_SPI_MOSI_PIN;
		GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
		GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_MOSI_GPIO_AF;
    GPIO_InitPeripheral(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
    GPIO_InitStructure.Pin = sFLASH_CS_PIN;
		GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
		GPIO_InitStructure.GPIO_Alternate = sFLASH_CS_GPIO_AF;
    GPIO_InitPeripheral(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}


/**
 * @brief  取消SPI闪存驱动器使用的外围设备的初始化。
 */
void sFLASH_DeInit(void)
{
    sFLASH_LowLevel_DeInit();
}

/**
 * @brief  初始化SPI闪存驱动器使用的外设。
 */
void sFLASH_Init(void)
{
    SPI_InitType SPI_InitStructure;

    sFLASH_LowLevel_Init();

    /*!< 片选拉高 */
    sFLASH_CS_HIGH();

    /*!< 配置SPI */
	  SPI_InitStruct(&SPI_InitStructure);
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;        //双线全双工
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;                      //主机模式
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;                  //数据宽度8
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;                      //配置为模式3
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;          //软件控制NSS

    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_8;     //8分频

    SPI_InitStructure.FirstBit = SPI_FB_MSB;                 //高位在前
    SPI_InitStructure.CRCPoly  = 7;                         
    SPI_Init(sFLASH_SPI, &SPI_InitStructure);

    /*!< Enable the sFLASH_SPI  */
    SPI_Enable(sFLASH_SPI, ENABLE);
}

/*以下部分针对flash操作*/

/**
 *擦除一个扇区
 *SectorAddr:扇区地址 0~511 for w25x16
 *擦除一个山区的最少时间:150ms
 */
void sFLASH_EraseSector(uint32_t SectorAddr)
{
    /*发送写使能指令 */
    sFLASH_WriteEnable();

    /* 扇区擦除 */
    /* 使能器件 */
    sFLASH_CS_LOW();
		SectorAddr *= sFLASH_SPI_PAGESIZE;
    /* 发送扇区擦除指令 */
    sFLASH_SendByte(sFLASH_CMD_SE);
    /* 发送24bit地址*/
    sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
    sFLASH_SendByte(SectorAddr & 0xFF);
    /* 取消片选 */
    sFLASH_CS_HIGH();

    /* 等待擦除完成 */
    sFLASH_WaitForWriteEnd();
}

void sFLASH_EraseBulk(void)
{
    /*!< Send write enable instruction */
    sFLASH_WriteEnable();

    /*!< Bulk Erase */
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();
    /*!< Send Bulk Erase instruction  */
    sFLASH_SendByte(sFLASH_CMD_BE);
    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
}


/**
 *擦除整个芯片
 *整片擦除时间:
 *W25X16:25s 
 *W25X32:40s 
 *W25X64:40s 
 *等待时间超长..
 */
void sFLASH_EraseChip(void)
{
    /*发送写使能指令*/
    sFLASH_WriteEnable();

    /* 片擦除 */
    /* 使能器件 */
    sFLASH_CS_LOW();
    /*发送片擦除命令 */
    sFLASH_SendByte(sFLASH_CMD_CE);
    /* 取消片选 */
    sFLASH_CS_HIGH();

    /* 等待擦除完成 */
    sFLASH_WaitForWriteEnd();
}

/**
 *SPI在一页(0~65535)内写入少于256个字节的数据
 *在指定地址开始写入最大256字节的数据
 *pBuffer:数据存储区
 *WriteAddr:开始写入的地址(24bit)
 *NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	
 */
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    /*发送写使能指令 */
    sFLASH_WriteEnable();

    /*使能器件 */
    sFLASH_CS_LOW();
    /*发送写页命令  */
    sFLASH_SendByte(sFLASH_CMD_WRITE);
    /*发送24bit地址   */
    sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    sFLASH_SendByte(WriteAddr & 0xFF);

    /*循环写数 */
    while (NumByteToWrite--)
    {
        /*!< Send the current byte */
        sFLASH_SendByte(*pBuffer);
        /*!< Point on the next byte to be written */
        pBuffer++;
    }

    /*取消片选 */
    sFLASH_CS_HIGH();

    /*等待擦除完成 */
    sFLASH_WaitForWriteEnd();
}

/**
 *写SPI FLASH  
 *在指定地址开始写入指定长度的数据
 *该函数带擦除操作!
 *pBuffer:数据存储区
 *WriteAddr:开始写入的地址(24bit)
 *NumByteToWrite:要写入的字节数(最大65535)  	
*/	   
//uint8_t SPI_FLASH_BUF[sFLASH_SPI_PAGESIZE];
void sFlash_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;  
	uint8_t * SPI_FLASH_BUF;
	SPI_FLASH_BUF = malloc(sFLASH_SPI_PAGESIZE);
	secpos = WriteAddr/sFLASH_SPI_PAGESIZE;//扇区地址 0~511 for w25x16
	secoff = WriteAddr%sFLASH_SPI_PAGESIZE;//在扇区内的偏移
	secremain=sFLASH_SPI_PAGESIZE-secoff;//扇区剩余空间大小 
    if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//不大于4096个字节
	while(1) 
	{
        sFLASH_Read(SPI_FLASH_BUF,secpos*sFLASH_SPI_PAGESIZE,sFLASH_SPI_PAGESIZE);//读出整个扇区的内容
        for(i=0;i<secremain;i++)//校验数据
		{
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;//需要擦除  	  
		}
        if(i<secremain)//需要擦除
		{
			sFLASH_EraseSector(secpos);//擦除这个扇区
			for(i=0;i<secremain;i++)	   //复制
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			sFlash_Write_NoCheck(SPI_FLASH_BUF,secpos*sFLASH_SPI_PAGESIZE,sFLASH_SPI_PAGESIZE);//写入整个扇区  

		}else sFlash_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumByteToWrite==secremain)break;//写入结束了
        else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0 	 

		   	pBuffer+=secremain;  //指针偏移
			WriteAddr+=secremain;//写地址偏移	   
		   	NumByteToWrite-=secremain;				//字节数递减
			if(NumByteToWrite>sFLASH_SPI_PAGESIZE)secremain=sFLASH_SPI_PAGESIZE;	//下一个扇区还是写不完
			else secremain=NumByteToWrite;			//下一个扇区可以写完了
		}	 
    }
		free(SPI_FLASH_BUF);
}
/**
 *无检验写SPI FLASH 
 *必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
 *具有自动换页功能 
 *在指定地址开始写入指定长度的数据,但是要确保地址不越界!
 *pBuffer:数据存储区
 *WriteAddr:开始写入的地址(24bit)
 *NumByteToWrite:要写入的字节数(最大65535)
 *CHECK OK
*/
void sFlash_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 			 		 
	uint16_t pageremain;	   
	pageremain=sFLASH_SPI_ONE_PAGE-WriteAddr%sFLASH_SPI_ONE_PAGE; //单页剩余的字节数		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
	while(1)
	{	   
		sFLASH_WritePage(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//写入结束了
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
			if(NumByteToWrite>sFLASH_SPI_ONE_PAGE)pageremain=sFLASH_SPI_ONE_PAGE; //一次可以写入256个字节
			else pageremain=NumByteToWrite; 	  //不够256个字节了
		}
	};	    
} 
/**
 *读取SPI FLASH  
 *在指定地址开始读取指定长度的数据
 *pBuffer:数据存储区
 *ReadAddr:开始读取的地址(24bit)
 *NumByteToRead:要读取的字节数(最大65535)
 */
void sFLASH_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    /*使能器件 */
    sFLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    sFLASH_SendByte(sFLASH_CMD_READ);

    /*发送24bit地址  */
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    sFLASH_SendByte(ReadAddr & 0xFF);

    while (NumByteToRead--) /*循环读数 */
    {
        *pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
        pBuffer++;
    }

    /*取消片选 */
    sFLASH_CS_HIGH();
}

/**
 * @brief  读取FLASH的ID
 * @return FLASH ID
 */
uint32_t sFLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    /*使能器件 */
    sFLASH_CS_LOW();

    /*!< Send "RDID " instruction */
    sFLASH_SendByte(0x9F);
    /*从flash里面读取一个字节 */
    Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

    /*从flash里面读取一个字节 */
    Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

    /*从flash里面读取一个字节 */
    Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

    /*取消片选 */
    sFLASH_CS_HIGH();

    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

    return Temp;
}

/**
 * @brief  读取芯片ID W25X16的ID:0XEF14
 * @return FLASH ID
 */
uint16_t SPI_Flash_ReadID(void)
{
	uint16_t Temp = 0;	  
	/*使能器件 */
    sFLASH_CS_LOW();			    
	sFLASH_SendByte(0x90);//发送读取ID命令	    
	sFLASH_SendByte(0x00); 	    
	sFLASH_SendByte(0x00); 	    
	sFLASH_SendByte(0x00); 	 			   
	Temp|=sFLASH_SendByte(0xFF)<<8;  
	Temp|=sFLASH_SendByte(0xFF);	 
	/*取消片选 */
    sFLASH_CS_HIGH();			    
	return Temp;
}  

/**
 * @brief  从SPI内读取一个字节数据
 * @return 返回读取到的数据
 */
uint8_t sFLASH_ReadByte(void)
{
    return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}

/**
 * @brief  通过SPI发送一个字节，同时读取一个字节数据
 * @return 返回读取到的数据
 */
uint8_t sFLASH_SendByte(uint8_t byte)
{
    /*等待发送寄存器为空*/
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;

    /*通过SPI发送一个数据*/
    SPI_I2S_TransmitData(sFLASH_SPI, byte);

    /*等待接收一个字节 */
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_RNE_FLAG) == RESET)
        ;

    /*返回读取到的一个字节数据 */
    return SPI_I2S_ReceiveData(sFLASH_SPI);
}

/**
 * @brief  通过SPI发送2个字节，同时读取2个字节数据
 * @return 返回读取到的数据
 */
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord)
{
    /*当DAT寄存器不为空时循环 */
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;

    /*通过sFLASH外设发送半字 */
    SPI_I2S_TransmitData(sFLASH_SPI, HalfWord);

    /*等待收到半字*/
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_RNE_FLAG) == RESET)
        ;

    /*返回读取到的半字数据*/
    return SPI_I2S_ReceiveData(sFLASH_SPI);
}

/**
 * 允许对FLASH进行写访问。
 */
void sFLASH_WriteEnable(void)
{
    /*使能器件  */
    sFLASH_CS_LOW();
    /*发送写使能 */
    sFLASH_SendByte(sFLASH_CMD_WREN);
    /* 取消片选 */
    sFLASH_CS_HIGH();
}

/**
 *读取SPI_FLASH的状态寄存器
 *BIT7  6   5   4   3   2   1   0
 *SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 *SPR:默认0,状态寄存器保护位,配合WP使用
 *TB,BP2,BP1,BP0:FLASH区域写保护设置
 *WEL:写使能锁定
 *BUSY:忙标记位(1,忙;0,空闲)
 *默认:0x00
 */
void sFLASH_WaitForWriteEnd(void)
{
    uint8_t flashstatus = 0;

    /*使能器件*/
    sFLASH_CS_LOW();

    /* 发送“读取状态注册”指令 */
    sFLASH_SendByte(sFLASH_CMD_RDSR);

    /*只要内存忙于写循环，就循环 */
    do
    {
        /*发送一个虚拟字节来生成FLASH所需的时钟并将状态寄存器的值放在FLASH_STS变量中 */
        flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    } while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* 等待BUSY位清空 */
    /*取消片选 */
    sFLASH_CS_HIGH();
}



/**
 *SPI在一页(0~65535)内写入少于256个字节的数据
 *在指定地址开始写入最大256字节的数据
 *pBuffer:数据存储区
 *WriteAddr:开始写入的地址(24bit)
 *NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	
 */
void sFLASH_DMA_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    /*发送写使能指令 */
    sFLASH_WriteEnable();

    /*使能器件 */
    sFLASH_CS_LOW();
    /*发送写页命令  */
    sFLASH_SendByte(sFLASH_CMD_WRITE);
    /*发送24bit地址   */
    sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    sFLASH_SendByte(WriteAddr & 0xFF);

		DMA_EnableChannel(sFLASH_SPI_Tx_DMA_Channel, DISABLE);
		sFLASH_SPI_Tx_DMA_Channel->MADDR = (uint32_t)pBuffer;
		DMA_SetCurrDataCounter(sFLASH_SPI_Tx_DMA_Channel,NumByteToWrite);
		
    DMA_EnableChannel(sFLASH_SPI_Tx_DMA_Channel, ENABLE);
		SPI_I2S_EnableDma(sFLASH_SPI, SPI_I2S_DMA_TX, ENABLE);
		
    while(!DMA_GetFlagStatus(sFLASH_SPI_Tx_DMA_FLAG, sFLASH_SPI_DMA));
    while(SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_BUSY_FLAG));                        
     
    SPI_I2S_EnableDma(sFLASH_SPI, SPI_I2S_DMA_TX, DISABLE);
    DMA_EnableChannel(sFLASH_SPI_Tx_DMA_Channel, DISABLE);
		
    /*取消片选 */
    sFLASH_CS_HIGH();

    /*等待擦除完成 */
    sFLASH_WaitForWriteEnd();
}


/**
 *读取SPI FLASH  
 *在指定地址开始读取指定长度的数据
 *pBuffer:数据存储区
 *ReadAddr:开始读取的地址(24bit)
 *NumByteToRead:要读取的字节数(最大65535)
 */
void sFLASH_DMARead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    /*使能器件 */
    sFLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    sFLASH_SendByte(sFLASH_CMD_READ);

    /*发送24bit地址  */
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    sFLASH_SendByte(ReadAddr & 0xFF);

    while (NumByteToRead--) /*循环读数 */
    {
        *pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
        pBuffer++;
    }
		DMA_EnableChannel(sFLASH_SPI_Rx_DMA_Channel, DISABLE);
		sFLASH_SPI_Rx_DMA_Channel->MADDR = (uint32_t)pBuffer;
		DMA_SetCurrDataCounter(sFLASH_SPI_Rx_DMA_Channel,NumByteToRead);
		
    DMA_EnableChannel(sFLASH_SPI_Rx_DMA_Channel, ENABLE);
		SPI_I2S_EnableDma(sFLASH_SPI, SPI_I2S_DMA_RX, ENABLE);
		
    while(!DMA_GetFlagStatus(sFLASH_SPI_Rx_DMA_FLAG, sFLASH_SPI_DMA));
    while(SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_BUSY_FLAG));                        
     
    SPI_I2S_EnableDma(sFLASH_SPI, SPI_I2S_DMA_RX, DISABLE);
    DMA_EnableChannel(sFLASH_SPI_Rx_DMA_Channel, DISABLE);

    /*取消片选 */
    sFLASH_CS_HIGH();
}
