/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-10     zhuangwei    first version
 */
// I2C2，引脚CAMDATA6(GPIO56)和CAMDATA7(GPIO57)的第四复用
// I2C鏁版嵁浼犺緭鏂瑰悜
#define LS1C_I2C_SDA2_GPIO56            (56)
#define LS1C_I2C_SCL2_GPIO57            (57)
#define LS1C_UART2_IRQ1   5
#define NULL ((void *)0)
#include "../libraries/ls1c_uart.h"
#include "../libraries/ls1c_irq.h"
#include "../libraries/ls1c_pin.h"
#include <rtthread.h>
#include "../libraries/ls1c_public.h" 
#include "../libraries/ls1c_gpio.h" 
#include "../libraries/ls1c_delay.h"
#include "../libraries/ls1c_i2c.h"

ls1c_i2c_info_t i2c_info;
//int slave_addr=0x50 >> 1;


void i2c_INT()
{

    // I2C2，引脚CAMDATA6(GPIO56)和CAMDATA7(GPIO57)的第四复用
    pin_set_remap(LS1C_I2C_SDA2_GPIO56, PIN_REMAP_FOURTH);
    pin_set_remap(LS1C_I2C_SCL2_GPIO57, PIN_REMAP_FOURTH);
    i2c_info.clock = 50*1000;       // 50kb/s
    i2c_info.I2Cx = LS1C_I2C_2;
    i2c_init(&i2c_info);
}





void test_uart_irqhandler(int IRQn, void *param)	//中断服务程序
{
    ls1c_uart_t uartx = uart_irqn_to_uartx(IRQn);
    void *uart_base = uart_get_base(uartx);
    unsigned char iir = reg_read_8(uart_base + LS1C_UART_IIR_OFFSET);
    int slave_addr = 0xb8 >> 1;

    // 判断是否为接收超时或接收到有效数据
    if ((IIR_RXTOUT & iir) || (IIR_RXRDY & iir))
    {
        // 是，则读取数据，并原样发送回去
        while (LSR_RXRDY & reg_read_8(uart_base + LS1C_UART_LSR_OFFSET))
        {
        	i2c_send_start_and_addr(&i2c_info, slave_addr, LS1C_I2C_DIRECTION_READ);
        	i2c_send_ack(&i2c_info);
        	i2c_send_data(&i2c_info,reg_read_8(uart_base+LS1C_UART_IIR_OFFSET),8);
        	i2c_send_stop(&i2c_info);
        }
    }

    return ;
}


void test_uart2_send_recv(void)						//初始化
{
    unsigned int tx_gpio = 37;
    unsigned int rx_gpio = 36;
    ls1c_uart_info_t uart2_info = {0};

    // 设置复用
    pin_set_remap(tx_gpio, PIN_REMAP_SECOND);
    pin_set_remap(rx_gpio, PIN_REMAP_SECOND);

    // 重新初始化串口2(使能接收中断)
    uart2_info.UARTx    = LS1C_UART2;
    uart2_info.baudrate = 115200;
    uart2_info.rx_enable= 1;         // 使能接收中断
    uart_init(&uart2_info);

    // 设置中断处理函数
    irq_install(LS1C_UART2_IRQ1);
    irq_enable(LS1C_UART2_IRQ1);

    while (1)
    {
        delay_s(1);
    }
}


int main(int argc, char **argv) 
{ 
	i2c_INT();   
	test_uart2_send_recv();
	return(0); 
} 

