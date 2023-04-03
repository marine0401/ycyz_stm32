#include "delay/delay.h"
#include "sys.h"



static u32 fac_us = 0;							//us��ʱ������




/**
 * @brief	��ʼ���ӳٺ���,SYSTICK��ʱ�ӹ̶�ΪAHBʱ��
 *
 * @param   SYSCLK	ϵͳʱ��Ƶ��
 *
 * @return  void
 */
void delay_init(u8 SYSCLK)
{
#if SYSTEM_SUPPORT_OS 						//�����Ҫ֧��OS.
    u32 reload;
#endif
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTickƵ��ΪHCLK
    fac_us = SYSCLK;						//�����Ƿ�ʹ��OS,fac_us����Ҫʹ��

#if SYSTEM_SUPPORT_OS 						//�����Ҫ֧��OS.
    reload = SYSCLK;					  //ÿ���ӵļ������� ��λΪK
    reload *= 1000000 / delay_ostickspersec;	//����delay_ostickspersec�趨���ʱ��
    //reloadΪ24λ�Ĵ���,���ֵ:16777216,��80M�£�Լ209.7ms����
    fac_ms = 1000 / delay_ostickspersec;		//����OS������ʱ�����ٵ�λ
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //����SYSTICK�ж�
    SysTick->LOAD = reload; 					//ÿ1/OS_TICKS_PER_SEC���ж�һ��
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //����SYSTICK
#else
#endif
}


/**
 * @brief	��ʱ΢��(us)����
 *
 * @remark	nus:0~190887435(���ֵ��2^32/fac_us@fac_us=22.5)
 *
 * @param   nus		��Ҫ��ʱ����΢��
 *
 * @return  void
 */
void delay_us(u32 nus)
{
    u32 ticks;
    u32 told, tnow, tcnt = 0;
    u32 reload = SysTick->LOAD;				//LOAD��ֵ
    ticks = nus * fac_us; 						//��Ҫ�Ľ�����
    told = SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ

    while(1)
    {
        tnow = SysTick->VAL;

        if(tnow != told)
        {
            if(tnow < told)tcnt += told - tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
            else tcnt += reload - tnow + told;
			
            told = tnow;
            if(tcnt >= ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
        }
    }
}


/**
 * @brief	��ʱ����(ms)����
 *
 * @param   nms		��Ҫ��ʱ���ٺ���
 *
 * @return  void
 */
void delay_ms(u16 nms)
{
    u32 i;

    for(i = 0; i < nms; i++) delay_us(1000);
}







