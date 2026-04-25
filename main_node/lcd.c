#include "delay.h"
#include "types.h"
#include "defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include<lpc21xx.h>

void writeLcd(u8 dat)
{
	WRITEBYTE(IOPIN0,LCD_DATA,dat);
	SSETBIT(IOSET0,LCD_EN);
	delay_us(1);
	SCLRBIT(IOCLR0,LCD_EN);
	delay_ms(2);
}
void cmdLcd(u8 cmd)
{
	SCLRBIT(IOCLR0,LCD_RS);//select rs reg as cmd reg
	writeLcd(cmd);
}

void InitLcd(void)

{

	delay_ms(15);

	WRITEBYTE(IODIR0,LCD_DATA,0xff);

	SETBIT(IODIR0,LCD_RS);//rs pin

	SETBIT(IODIR0,LCD_EN);//en pin

	cmdLcd(0x30);

	delay_ms(5);

	cmdLcd(0x30);

	delay_us(100);

	cmdLcd(0x30);

	cmdLcd(MODE_8BIT_2LINE);

	cmdLcd(DSP_ON_CUR_BLINK);

	cmdLcd(CLEAR_LCD);

	cmdLcd(SHIFT_CUR_RIGHT);

}

void charLcd(u8 asciival)
{
	SSETBIT(IOSET0,LCD_RS);
	writeLcd(asciival);
}

void strLcd(s8 *s)
{
	while(*s)
	{
		charLcd(*s++);
	}
}

void U32Lcd(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
	{
		charLcd('0');
	}
	else
	{
		while(n)
		{
			a[i]=(n%10)+48;
			n/=10;
			i++;
		}
		for(--i;i>=0;i--)
		{
			charLcd(a[i]);
		}
	}
}

void S32Lcd(s32 n)
{
	if(n<0)
	{
		charLcd('-');
		n=-n;
	}
	U32Lcd(n);
}

void F32Lcd(f32 n,u32 ndp)
{
	u32 i,t;
	if(n<0)
	{
		charLcd('-');
		n=-n;
	}
	t=n;
	U32Lcd(t);
	charLcd('.');
	for(i=0;i<ndp;i++)
	{
		n=(n-t)*10;
		t=n;
		charLcd(t+48);
	}
}		
	  
void HexLcd(u32 n)
{
	s32 i=0;
	u8 a[8];
	if(n==0)
	{
		charLcd('0');
	}
	else
	{
		while(n)
		{
			a[i]=(n%16);
			a[i]=((a[i]<=9)?(a[i]+48):((a[i]-10)+65));
			i++;
			n/=16;
		}
		for(--i;i>=0;i--)
		{
			charLcd(a[i]);
		}
	}
}

void BinLcd(u32 n,s32 nbd)
{
	s32 i;
	for(i=(nbd-1);i>=0;i--)
	{
		charLcd(READBIT(n,i)+48);
	}
}

void OctLcd(u32 n)
{
	s32 i=0;
	u8 a[8];
	if(n==0)
	{
		charLcd('0');
	}
	else
	{
		while(n)
		{
			a[i]=(n%8)+48;
			i++;
			n/=8;
		}
		for(--i;i>=0;i--)
		{
			charLcd(a[i]);
		}
	}
}

void BuildCGRAM(u8 *p,u32 nBytes)
{
	u32 i;
	cmdLcd(GOTO_CGRAM_START);
	for(i=0;i<nBytes;i++)
	{
		charLcd(p[i]);
	}
	cmdLcd(GOTO_LINE1_POS0);
}
