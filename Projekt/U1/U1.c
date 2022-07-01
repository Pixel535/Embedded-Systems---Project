#include <REGX52.H>

#define ON  0
#define OFF 1
#define No_Key 0x0C
#define Warunek (Key_3&Key_2&Key_1)==0

sbit LED = P0^0;
unsigned char NumCounter = 0;
unsigned char code Kod[] = {0x7F,0xBF,0xDF,0xEF}; 
unsigned char bdata Key;
sbit Key_3 = Key^3;
sbit Key_2 = Key^2;
sbit Key_1 = Key^1;

void Delay(void)
{
   unsigned char data x,y;
   for(x=0;x<150;x++)
      {
         for(y=0;y<150;y++) {;}
      }
}

void Delay2(void)
{
   unsigned char data x,y;
   for(x=0;x<70;x++)
      {
         for(y=0;y<70;y++) {;}
      }
}

void Zapal(unsigned char IloscZapalen)
{
	unsigned char i = 0;
	while(i < IloscZapalen)
	{
		LED = ON; Delay2(); LED = OFF; Delay2();
		i++;
	}
}

unsigned char KtoryPrzyciskWcisniety(unsigned char Kod_przycisku) 
 {
   unsigned char data Value, licznik;                               
   unsigned char code Koder[] = {0xE7,0xEB,0xED,0xD7,0xDB,0xDD,0xB7,0xBB,0xBD,0x77,0x7B,0x7D};    
   unsigned char code New_Char[] = {'1','2','3','4','5','6','7','8','9','*','0','#'};                         
   
   licznik=0x00;                                                    
   while((Koder[licznik]!=Kod_przycisku)&&(licznik<No_Key)){licznik++;} 
   Value = No_Key;
   if(licznik!=No_Key){Value = New_Char[licznik];}                  
   return Value;                                                    
 }

	void WcisnieciePrzycisku (void)  
  {
    unsigned char data Value, i = 0;
		unsigned char isCalling = 0;
		unsigned char isHash = 0;
    Value = KtoryPrzyciskWcisniety(Key);     
    if(Value != No_Key)        
      {
        if(Value == '1') {Zapal(1); NumCounter++;}
				else if(Value == '2') {Zapal(2); NumCounter++;}
				else if(Value == '3') {Zapal(3); NumCounter++;}
				else if(Value == '4') {Zapal(4); NumCounter++;}
				else if(Value == '5') {Zapal(5); NumCounter++;}
				else if(Value == '6') {Zapal(6); NumCounter++;}
				else if(Value == '7') {Zapal(7); NumCounter++;}
				else if(Value == '8') {Zapal(8); NumCounter++;}
				else if(Value == '9') {Zapal(9); NumCounter++;}
				else if(Value == '0') {Zapal(0); NumCounter++;}
				else if(Value == '*') {isCalling = 1;}
				else if(Value == '#') {isHash = 1;}
				
				if(isCalling == 1 && NumCounter == 9)
				{
					while(i < 4)
					{
						LED = ON; Delay(); Delay2(); LED = OFF; Delay(); Delay2();
						i++;
					}
					i = 0;
					while(i < 2)
					{
						LED = ON; Delay2(); LED = OFF; Delay2();
						i++;
					}
					NumCounter = 0;
				}
				else if(isCalling == 1 && NumCounter != 9)
				{
					while(i < 2)
					{
						LED = ON; Delay2(); LED = OFF; Delay2(); LED = ON; Delay2(); LED = OFF; Delay();
						i++;
					}
					NumCounter = 0;
				}
				else if(isHash == 1)
				{
					while(i < 1)
					{
						LED = ON; Delay2(); LED = OFF; Delay2(); LED = ON; Delay2(); LED = OFF; Delay();
						i++;
					}
					NumCounter = 0;
				}
				P3_1 = Value;
      }  
  }  
	
void main(void)  
{
  unsigned char data ind = 0;
	bit Zezwalaj = 1; 	      
  while(1) 
	{
		P2 = Kod[ind]; 
		Key = P2;
		if (Warunek)
		{
			if (Zezwalaj == 1)
			{
				WcisnieciePrzycisku(); 
				Zezwalaj = 0;
			}
		}
		else
		{
			if (ind<3) {ind++;}
			else {ind = 0;}
			Zezwalaj = 1;
		}
	} 
}