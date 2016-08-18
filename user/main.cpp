/**
  ******************************************************************************
  * @file   : *.cpp
  * @author : shentq
  * @version: V1.2
  * @date   : 2016/08/14

  * @brief   ebox application example .
  *
  * Copyright 2016 shentq. All Rights Reserved.         
  ******************************************************************************
 */

/*
一个简单的命令帧接收示例
*/
#include "ebox.h"



u8 count;

void test()
{
    uint8_t c;
    c = uart1.receive();
    uart1.put_char(c);
}

void test1()
{
    count++;
    PB8.toggle();
}
void setup()
{
    ebox_init();
    uart1.begin(115200);
    uart1.attach(test,RxIrq);
    uart1.attach(test1,TxIrq);
    PB8.mode(OUTPUT_PP);
    PB8.reset();
}

int main(void)
{

    setup();

    while(1)
    {
        uart1.printf("uart is ok ! count = %d\r\n", count);
        delay_ms(1000);
    }


}




