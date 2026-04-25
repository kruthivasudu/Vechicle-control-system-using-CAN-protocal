#include<lpc21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "lcd.h"  
#include "can.h"
#include "can_defines.h"
//#include "lcd_defines.h"

int ReadTemp(void);
void Init_EXTINT(void);

int main() 
{
	extern struct CAN_Frame TX;	
	struct CAN_Frame rx;
	int temp;
	unsigned char tp,tpd;
	Init_EXTINT();
  	InitLcd();
	Init_CAN1();
	cmdLcd(0x0c);
	TX.ID=1;
	TX.vbf.RTR=0;
	TX.vbf.DLC=1;
	IODIR0|=1<<17;
	while(1) 
	{
		temp=ReadTemp();  //READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCOL
		tp  = temp>>4;	  //GETTING INTEGER PART
		tpd=temp&0x08?0x35:0x30;//GETTING FRACTIONAL PART
		cmdLcd(0x80);
		strLcd("ENG Temp=");
		U32Lcd(tp);
		charLcd('.');
		charLcd(tpd);
		strLcd(" C  ");	 
		CAN1_Rx(&rx);
		//if(rx.ID==2)
		//{
		//	rx.Data[0]=C1RDA;
			cmdLcd(0xc0);
			strLcd("Distance ");
			U32Lcd(rx.Data[0]);
		//}
		if(rx.Data[0]<20)
			IOCLR0=1<<17;
		else
			IOSET0=1<<17; 
	}
}
