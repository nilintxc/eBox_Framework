/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

//STM32 RUN IN eBox
#include "ebox.h"
#include "bsp_ebox.h"

#include "at24c02.h"

/**
	*	1	此例程需要调用eDrive目录下的si4432驱动
	*	2	此例程演示了si4432无线模块收发
	*/

/* 定义例程名和例程发布日期 */
#define EXAMPLE_NAME	"si4432 example"
#define EXAMPLE_DATE	"2018-08-11"

At24c02 ee(&I2C);
uint8_t data;

void setup()
{
    ebox_init();
    UART.begin(115200);
    print_log(EXAMPLE_NAME,EXAMPLE_DATE);
    UART.printf("pin id 0x%x , 0x%x",PB10.id,PB11.id );
    ee.begin(1);
//  	I2C.begin(1);

}
int16_t x, i;
uint8_t wbuf[512];
uint8_t rbuf[512];
#define MAX_LEN 10
int ret = 0;
int main(void)
{
    setup();
    
    while(1)
    {
        uart1.printf("\r\n=================wbuf================\r\n");
        for(uint16_t i = 0; i < MAX_LEN; i++)
        {
            wbuf[i] = random() % 256;
        }
        for(uint16_t i = 0; i < MAX_LEN; i++)
        {
                uart1.printf(" %02x ", wbuf[i ]);
                //ee.byteWrite(i*16+j,buf[i*16+j]);
        }
        I2C.writeBuf(0xA0,0x00,wbuf,MAX_LEN);
        I2C.checkBusy(0xA0);
        uart1.printf("\r\n==================rbuf==============\r\n");
        I2C.readBuf(0xA0,0x00,rbuf,MAX_LEN);

        for(uint16_t i = 0; i < MAX_LEN; i++)
        {
                uart1.printf(" %02x ", rbuf[i]);
        }

        for(i = 0xa0;i< 0xb0;i++){
            UART.printf("slave address 0x%02x check busy %d \r\n",i,I2C.checkBusy(i));
            delay_ms(500);
        }
        delay_ms(15000);
    }


//    while(1)
//    {
//        ret = 0;

//        uart1.printf("=================wbuf================\r\n");
//        for(uint16_t i = 0; i < MAX_LEN; i++)
//        {
//            wbuf[i] = random() % 256;
//        }
//        for(uint16_t i = 0; i < MAX_LEN; i++)
//        {
//                uart1.printf(" %02x ", wbuf[i ]);
//                //ee.byteWrite(i*16+j,buf[i*16+j]);
//        }
//        uart1.printf("\r\n ");
//        ee.write_byte(256, wbuf, MAX_LEN);

//        uart1.printf("==================rbuf==============\r\n");

//        data = ee.read_byte(256, rbuf, MAX_LEN);
//        for(uint16_t i = 0; i < MAX_LEN; i++)
//        {
//                uart1.printf(" %02x ", rbuf[i]);
//        }
//        uart1.printf("\r\n ");
//        for(int i = 0; i < MAX_LEN; i++)
//        {
//            if(wbuf[i] != rbuf[i])
//            {
//                ret = 1;
//                break;
//            }
//        }
//        if(ret == 1)
//        {
//            uart1.printf("eeprom check ......[err]");
//            ee.begin(4000);
//        }
//        else
//            uart1.printf("eeprom check ......[OK]");
//            
//        uart1.printf("\r\n================================\r\n");
//        delay_ms(1000);
//    }


}




