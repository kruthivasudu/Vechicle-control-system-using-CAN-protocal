#include<lpc21xx.h>
#include "types.h"
#include "defines.h"
#include "adc_defines.h"
//#include "lcd.h"
#include "can.h"
#include "delay.h"

void Init_ADC(void);
f32 Read_ADC(u8);
u32 aR0;
int main(void) 
{	
	struct CAN_Frame TX;
  	Init_ADC();
	//InitLcd();
	Init_CAN1();
	TX.ID=2;
	TX.vbf.RTR=0;
	TX.vbf.DLC=1;
	while(1) 
	{
	//	cmdLcd(0x01);
	//	strLcd("DISTANCE=");
    	aR0=Read_ADC(CH1);
		U32Lcd(aR0);
		TX.Data[0]=aR0;
		CAN1_Tx(TX);
		delay_ms(500);
	}
}
