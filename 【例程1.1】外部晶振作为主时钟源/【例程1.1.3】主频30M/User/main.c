/************************************************************************************** 
*   ����    ��2013��11��6��  
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz
*   ����    ������LPC1114��ƵΪ30M��CLKOUT����Ƶ250��Ƶ���������120K�ķ���
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "LPC11XX.H"


/***********************************************/
/*  �������ܣ�ʹ��CLKOUT�����Ƶ��             */
/*  ��ڲ�����CLKOUT_DIV,��CLKOUT��Ƶֵ��1~255 */
/*             =0 �ر�ʱ�����                 */
/*  ˵����    �˺�������������ʱ��             */
/***********************************************/
void CLKOUT_EN(uint8_t CLKOUT_DIV)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);          // ʹ��IOCONʱ�� 
	LPC_IOCON->PIO0_1=0XD1;						             // ��P0.1������ΪCLKOUT����
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);         // ����IOCONʱ��
	LPC_SYSCON->CLKOUTDIV   = CLKOUT_DIV;			     // CLKOUTʱ��ֵ���=��ʱ��/CLKOUT_DIV
	LPC_SYSCON->CLKOUTCLKSEL= 0X00000003;	  		   // CLKOUTʱ��Դѡ��Ϊ��ʱ��
	LPC_SYSCON->CLKOUTUEN   =0;
	LPC_SYSCON->CLKOUTUEN   =1;
	while (!(LPC_SYSCON->CLKOUTUEN & 0x01));       // ȷ��ʱ��Դ���º�����ִ��
}

/************************************************/
/*                    ������                    */
/************************************************/
int main(void)
{
	CLKOUT_EN(250);// CLKOUTʱ��ֵ���=30M/250=120K
	
	while(1)
	{
		;
	}
}
