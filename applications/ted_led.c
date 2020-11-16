/*  * File      : test_led.c 测试 led 接口在 finsh/msh 中运行 1. test_led() / test_led */ 
#include <rtthread.h> 
#include "../libraries/ls1c_public.h" 
#include "../libraries/ls1c_gpio.h" 
#include "../libraries/ls1c_delay.h" 
#define led_gpio 52 
 
/*  * 测试库中 gpio 作为输出时的相关接口  * led 闪烁 10 次  */ 
void test_led(void) 
{     
	int i; 
     // 初始化     
	 rt_kprintf("Init led! \n");     
	 gpio_init(led_gpio, gpio_mode_output);     
	 gpio_set(led_gpio, gpio_level_high);       // 指示灯默认熄灭 
 
    // 输出 10 个矩形波，如果 gpio50 上有 led，则可以看见 led 闪烁 10 次     
	for (i=0; i<30; i++)     
	{         
		gpio_set(led_gpio, gpio_level_low);         
		delay_s(100);         
		gpio_set(led_gpio, gpio_level_high);         
		delay_s(100);     
		rt_kprintf("current time: %d \n", i);     
	}          
	return ; 
} 
 
#include  <finsh.h>  
FINSH_FUNCTION_EXPORT(test_led, test_led  e.g.test_led()); 
/* 导出到 msh 命令列表中 */ 
MSH_CMD_EXPORT(test_led, test led flash );