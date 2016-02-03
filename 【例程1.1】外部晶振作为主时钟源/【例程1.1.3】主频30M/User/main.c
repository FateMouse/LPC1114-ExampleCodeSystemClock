/************************************************************************************** 
*   日期    ：2013年11月6日  
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz
*   功能    ：配置LPC1114主频为30M，CLKOUT把主频250分频后，引脚输出120K的方波
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "LPC11XX.H"


/***********************************************/
/*  函数功能：使能CLKOUT脚输出频率             */
/*  入口参数：CLKOUT_DIV,即CLKOUT分频值，1~255 */
/*             =0 关闭时钟输出                 */
/*  说明：    此函数可用来测试时钟             */
/***********************************************/
void CLKOUT_EN(uint8_t CLKOUT_DIV)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);          // 使能IOCON时钟 
	LPC_IOCON->PIO0_1=0XD1;						             // 把P0.1脚设置为CLKOUT引脚
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);         // 禁能IOCON时钟
	LPC_SYSCON->CLKOUTDIV   = CLKOUT_DIV;			     // CLKOUT时钟值输出=主时钟/CLKOUT_DIV
	LPC_SYSCON->CLKOUTCLKSEL= 0X00000003;	  		   // CLKOUT时钟源选择为主时钟
	LPC_SYSCON->CLKOUTUEN   =0;
	LPC_SYSCON->CLKOUTUEN   =1;
	while (!(LPC_SYSCON->CLKOUTUEN & 0x01));       // 确定时钟源更新后向下执行
}

/************************************************/
/*                    主函数                    */
/************************************************/
int main(void)
{
	CLKOUT_EN(250);// CLKOUT时钟值输出=30M/250=120K
	
	while(1)
	{
		;
	}
}
