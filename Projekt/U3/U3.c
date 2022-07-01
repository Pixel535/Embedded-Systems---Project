#include <REGX52.H>

unsigned char xdata LeftNum _at_ 0xFE00;
unsigned char xdata RightNum _at_ 0xFD00;
sbit Button = P3^2;

unsigned char code numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned char Leftidx_numbers;
unsigned char Rightidx_numbers;
unsigned char Leftidx_letters;
unsigned char Rightidx_letters;
unsigned char code letters[] = {0x76, 0x06};
unsigned char isLetter = 0;

void Delay(void)
{
   unsigned char i;
   unsigned char j;
   for(i=0;i<150;i++)
   {
      for(j=0;j<200;j++)
      { ; }
   }
}

void ISR_Timer(void) interrupt 3
{
	if(isLetter == 0)
	{
		LeftNum = numbers[Leftidx_numbers];
		RightNum = numbers[Rightidx_numbers];
	}
	else if(isLetter == 1)
	{
		LeftNum = letters[Leftidx_letters];
		RightNum = letters[Rightidx_letters];
	}
}

void Init(void)
{
	TCON = 0x00;
	TMOD = TMOD & 0x0F;
	TMOD = TMOD | 0x20;
	TL1 = TH1 = 0x00;
	ET1 = 1;
	EA = 1;
	TR1 = 1;
}

void Int0() interrupt 0		
 {
 	EX0 = 0;
	Leftidx_numbers = 1;
	Rightidx_numbers = 0;
	isLetter = 0;
	EX0 = 1;	
 }
 
 void initialize()				   
 {
	IT0 = 1;	
	EX0 = 1;	
	EA = 1;		
 }

void main(void)
{
	Init();
	initialize();
	Leftidx_numbers = 1;
	Rightidx_numbers = 0;
	while(1)
	{
		Delay();
		if(Rightidx_numbers > 0)
		{
			isLetter = 0;
			Leftidx_numbers = 0;
			Rightidx_numbers--;
		}
		else if(Rightidx_numbers == 0 && Leftidx_numbers != 0)
		{
			isLetter = 0;
			Leftidx_numbers = 0;
			Rightidx_numbers = 9;
		}
		else if(Rightidx_numbers == 0 && Leftidx_numbers == 0)
		{
			isLetter = 1;
			Leftidx_letters = 0;
			Rightidx_letters = 1;
		}
	}
}