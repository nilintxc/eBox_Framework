/**
  ******************************************************************************
  * @file    bsp_ebox.cpp
  * @author  cat_li	
  * @version V1.0
  * @date    2018/07/31
  * @brief   硬件相关信息声明
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form 
  * or means, without the prior written consent of shentq. This specification is 
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "bsp_ebox.h"
#include "ebox_mem.h"

//Button  btn(&BtnPin,1);
//// 依赖edrive目录下 led模块
//Led     led1(&LED1,0);
//Led     led2(&LED2,0);
//Led     led3(&LED3,0);
//Lcd lcd(&PB5, &PB6, &PB4, &PB3, &spi1);
W5500Class w5500(&PC13, &PC14, &PC15, &spi2);

// 如果不使用object.cpp, 使用下列方式创建IO对象
//mcuGpio 		LED1(GPIOB,GPIO_Pin_8);
//mcuGpio 		LED2(GPIOB,GPIO_Pin_9);
//mcuGpio 		LED3(GPIOB,GPIO_Pin_10);

//mcuGpio		BtnPin(GPIOA,GPIO_Pin_8);
//Uart 			UART(USART1, &PA9, &PA10);


// 使用object.cpp,使用下列方式重命名IO对象，可以减少code区消耗
//#define   LED1  PB8
//#define   LED2  PB9
//#define   LED3  PB10

//#define   BtnPin	PA8
#define   UART	uart1


/*
*********************************************************************************************************
*	函 数 名: PrintfLog
*	功能说明: 打印例程名称和例程发布日期, 接上串口线后，打开PC机的超级终端软件可以观察结果
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void print_log(const char *name,const char *date)
{
	UART.print("\n\r");
	UART.print("*************************************************************\n\r");
	UART.print("* \r\n");	                /* 打印一行空格 */
	UART.print("* 例程名称      : ");	    /* 打印例程名称 */
    UART.println(name);
	UART.print("* 发布日期      : ");	    /* 打印例程日期 */
    UART.println(date);

	UART.print("* 硬件平台      : ");       /* 硬件平台 */
    UART.println(HARDWARE);
	UART.print("* EBOX库版本    : ebox_" );/* 版本信息 */
    UART.println(EBOX_VERSION);
	UART.print("*                     CPU 信息\r\n");	/* CPU信息 */
	UART.println();	
	UART.print("* CPU TYPE      : ");	    /* 打印CPU类型 */
	UART.println(MCU_TYPE);	
	UART.print("* CPU PINS      : ");	    /* 打印CPU引脚数量 */
	UART.println(STM32_PINS);	
	UART.print("* CPU COMPANY   : ");	    /* 打印CPU公司 */
	UART.println(MCU_COMPANY);	
    
    
	UART.print("* CPUID         : ");       /* 打印CPU唯一ID */
	UART.print(cpu.chip_id[2],HEX);	
	UART.print(cpu.chip_id[1],HEX);	
	UART.println(cpu.chip_id[0],HEX);	
    
    
	UART.print("* core          : ");
	UART.print(cpu.clock.core/1000000.0);	/* 打印时钟树信息 */
    UART.println("Mhz");
    UART.print("* hclk          : ");
	UART.print(cpu.clock.hclk/1000000.0);	
    UART.println("Mhz");
    UART.print("* pclk1         : ");
	UART.print(cpu.clock.pclk1/1000000.0);	
    UART.println("Mhz");
    UART.print("* pclk2         : ");
	UART.print(cpu.clock.pclk2/1000000.0);
    UART.println("Mhz");

    
	UART.print("* flash size    : ");       /* 打印flash大小 */
	UART.print(cpu.flash_size);	
    UART.println("KB");
    
	UART.print("* flash used    : ");	    /* 打印flash使用了多少KB */   
	UART.print(MCU_FLASH_USED/1024.0);	
    UART.println("KB");
    
	UART.print("* flash remaind : ");	    /* 打印flash剩余了多少KB  */ 
	UART.print(MCU_FLASH_REMAIND/1024.0);	
    UART.println("KB");
    
	UART.print("* mem size      : ");       /* 打印SRAM大小 */
	UART.print(MCU_SRAM1_SIZE/1024.0);	
    UART.println("KB");
    
	UART.print("* mem used      : ");	    /* 打印SRAM使用了多少KB */   
	UART.print(MCU_SRAM1_USED/1024.0);	
    UART.println("KB");
    
	UART.print("* mem remaind   : ");	    /* 打印SRAM剩余了多少KB */   
	UART.print(MCU_SRAM1_REMAIND/1024.0);	
    UART.println("KB");
    
	UART.print("* heap used     : ");	    /* 打印heap使用率 */   
	UART.print(ebox_mem_used()/1024.0);	
	UART.println("%");	
    
	UART.print("* heap free     : ");	    /* 打印heap使用了多少KB */   
	UART.print(ebox_get_free()/1024.0);
    UART.println("KB");
    
	UART.print("* \r\n");	                /* 打印一行空格 */
	UART.print("*************************************************************\n\r");
}



