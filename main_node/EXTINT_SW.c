#include<lpc21xx.h>
#include "can.h"

int R_flag=0,L_flag=0;
struct CAN_Frame TX;

void RIGHT_ISR(void) __irq
{
	if(R_flag==0)
	{
		
		TX.Data[0]='R';
		R_flag=1;
		L_flag=0;
		CAN1_Tx(TX);
	}
	else
	{
		R_flag=0;
		TX.Data[0]=0;
		CAN1_Tx(TX);
	}
	EXTINT=1<<1;
	VICVectAddr=0;	
}

void LEFT_ISR(void) __irq
{
	if(L_flag==0)
	{
		TX.Data[0]='L';
		L_flag=1;
		R_flag=0;
		CAN1_Tx(TX);
	}
	else
	{
		L_flag=0;
		TX.Data[0]=0;
		CAN1_Tx(TX);
	}
	EXTINT=1<<2;
	VICVectAddr=0;	
}

void Init_EXTINT(void)
{
//	PINSEL0|=0xcc;
	PINSEL0|=0x20000000|0xA0000000;
	VICIntEnable|=1<<15|1<<16;
	VICVectCntl0=1<<5|15;
	VICVectCntl1=1<<5|16;
	VICVectAddr0=(unsigned int) RIGHT_ISR;
	VICVectAddr1=(unsigned int)	LEFT_ISR;
	EXTINT=1<<1|1<<2;//0x06;
	EXTMODE=1<<1|1<<2;//0x06;
	EXTPOLAR=1<<1|1<<2;//0x06;
}
