#include "types.h"

void InitLcd(void);
void writeLcd(u8);
void cmdLcd(u8);
void charLcd(u8);
void strLcd(s8 *);
void U32Lcd(u32);
void S32Lcd(s32);
void F32Lcd(f32,u32);
void BinLcd(u32,s32);
void HexLcd(u32);
void OctLcd(u32);
void BuildCGRAM(u8*,u32);

