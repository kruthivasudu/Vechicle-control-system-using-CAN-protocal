#include<lpc21xx.h>
#include "types.h"

#include "defines.h"

#include "adc_defines.h"

#include "delay.h"


void Init_ADC(void)

{

  ADCR=PDN_BIT|CLKDIV|CH1;	

}


f32 Read_ADC(u8 chNo)

{ 
 u32 range;

  u16 adcVal=0;

	WRITEBYTE(ADCR,0,chNo);

	SETBIT(ADCR,ADC_START_BIT);

	delay_us(3);

	while(!READBIT(ADDR,DONE_BIT));

	CLRBIT(ADCR,ADC_START_BIT);

	adcVal=(ADDR>>6)&0x3FF;
	range=(6787/(adcVal-3)-4);

	return range;
}
