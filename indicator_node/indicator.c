#include<lpc21xx.h>
#include "delay.h"
#include "defines.h"
#include "can.h"
#include "can_defines.h"
#define LEDS 0

int R_flag=0,L_flag=0;

int main()
{
	struct CAN_Frame rx;
	int i=0;
	Init_CAN1();
	IODIR0|=0xff; 
	IOPIN0|=0xff; 
	while(1)
	{					 
	 	CAN1_Rx(&rx);
		while((C1GSR&RBS_BIT_READ)==0)
		{
			if(rx.Data[0]=='R')
			{
				for(i=3;i>=LEDS;i--)
					{
						SSETBIT(IOCLR0,i);
						delay_ms(200);
						SCLRBIT(IOSET0,i);
					}
			}
			else if(rx.Data[0]=='L')
			{
					for(i=4;i<=7;i++)
					{
						SSETBIT(IOCLR0,i);
						delay_ms(200);
						SCLRBIT(IOSET0,i);
					}
			}
			else
			{
				IOPIN0|=0xff;
			}
		}	
	}
}
