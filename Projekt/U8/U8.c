#include <REGX52.H>

#define False    			0  
#define True     			1

#define LCD_RS    P2_4
#define LCD_RW    P2_5
#define LCD_E     P2_6
#define LCD_DB4   P2_0
#define LCD_DB5   P2_1
#define LCD_DB6   P2_2
#define LCD_DB7   P2_3

#define LCD_DISPLAY_ON		  0x0C
#define LCD_ENTRY_MODE		  0x06
#define LCD_CURSOR_COM		  0x0F
#define LCD_CLEAR		        0x01
#define LCD_CONFIG		      0x28
#define LCD_DISPLAY_OFF		  0x08
#define LCD_CURSOR_BLINK	  0x0D


static unsigned char code Screen1[] = "  SWB  PROJEKT  "
                                      " |   _[@@]/    |"
																			" |    d  b	    |"	
                                      " MATEUSZ  GAJDA ";
																			
static unsigned char code Screen2[] = "  SWB  PROJEKT  "
                                      " /   _[@@]_    )"
																			" /    d  b	    )"	
                                      " MATEUSZ  GAJDA ";

static unsigned char code Screen3[] = "  SWB  PROJEKT  "
                                      " -   _[@@]/    -"
																			" -    d  b	    -"	
                                      " MATEUSZ  GAJDA ";
																			
static unsigned char code Screen4[] = "  SWB  PROJEKT  "
                                      " )   _[@@]_    /"
																			" )    d  b	    /"	
                                      " MATEUSZ  GAJDA ";	

static unsigned char code Screen5[] = "  SWB  PROJEKT  "
                                      " |   _[@@]/    |"
																			" |    d  b	    |"	
                                      " MATEUSZ  GAJDA ";
																			
unsigned char LOADING[] = {'L', 'O', 'A', 'D', 'I', 'N', 'G'};
unsigned char LoadingBar[] = {'X'};
unsigned char DotAndSpace[] = {'.', ' '};
unsigned char Percentage[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '%'};
 
void Delay(void)//60ms
{
   unsigned char data x,y;
   for(x=0;x<50;x++)
      {
         for(y=0;y<50;y++) {;}
      }
}

void Delay2(void)//1ms
{
   unsigned char data x,y;
   for(x=0;x<10;x++)
      {
         for(y=0;y<10;y++) {;}
      }
}

void Delay3(void)//5ms
{
   unsigned char data x,y;
   for(x=0;x<15;x++)
      {
         for(y=0;y<15;y++) {;}
      }
}

void Delay4(void)
{
   unsigned char data x,y;
   for(x=0;x<100;x++)
      {
         for(y=0;y<100;y++) {;}
      }
}

void Lcd_SendCommand (unsigned char LcdCommand)
 {
   unsigned char Lcd_Comm = 0;
   static bit LCDReady;
    
   LCD_RS = False;
   LCD_RW = False;

   Lcd_Comm = LcdCommand >> 4;
   P2 = P2 & 0xF0;
   P2 = P2 | Lcd_Comm;

   LCD_E = True;
   LCD_E = False;

   Lcd_Comm = LcdCommand & 0x0F;  
   P2 = P2 & 0xF0;      
   P2 = P2 | Lcd_Comm;

   LCD_E = True;
   LCD_E = False;

   P2 = P2 | 0x0F;     

   LCD_RW = True;
   LCD_RS = False;
   
   LCDReady = 1;
   while (LCDReady == 1)
   {
      LCD_E = True;
      LCDReady = LCD_DB7;
      LCD_E	= False;
      LCD_E = True;
      LCD_E	= False;
   }          
 }
 
 static void Lcd_SendData (unsigned char LcdData)
 {
   unsigned char Lcd_Data = 0;
   static bit LCDReady;
 
   LCD_RS = True;
   LCD_RW = False;

   Lcd_Data = LcdData >> 4;
   P2 = P2 & 0xF0;
   P2 = P2 | Lcd_Data;

   LCD_E = True;
   LCD_E = False;

   Lcd_Data = LcdData & 0x0F;  
   P2 = P2 & 0xF0;   
   P2 = P2 | Lcd_Data;

   LCD_E = True;
   LCD_E = False;

   P2 = P2 | 0x0F;

   LCD_RW = True;
   LCD_RS = False;
   
   LCDReady = 1;
   while (LCDReady == 1)
   {
     LCD_E = True;
     LCDReady = LCD_DB7;
     LCD_E	= False;
   	 LCD_E	= True;
   	 LCD_E	= False;
   }             
 }
 
 void Lcd_DisplayChar (char Singlechar)
 {
   Lcd_SendData(Singlechar);
 }
 
 void Lcd_Cursor (char row, char column)
 {
   if (row == 1) Lcd_SendCommand (0x80 + column - 1);
   if (row == 2) Lcd_SendCommand (0xC0 + column - 1);
   if (row == 3) Lcd_SendCommand (0x90 + column - 1);
   if (row == 4) Lcd_SendCommand (0xD0 + column - 1);
 }
 
 void Lcd_DisplayRow (char row, char *string)
 {
   char i;
   Lcd_Cursor (row, 1);
   for (i=0; i<16; i++) Lcd_DisplayChar (*string++);
 }
 
 void Lcd_DisplayScreen (char *ptr)
 {
   Lcd_DisplayRow(1,ptr +  0);
   Lcd_DisplayRow(2,ptr + 16);
   Lcd_DisplayRow(3,ptr + 32);
   Lcd_DisplayRow(4,ptr + 48);
 }
	
 void LcdLoading(void)
 {
    unsigned char index = 0;
	  unsigned char i = 0;
	  unsigned char DotsNumber = 0;
	  unsigned char DidCycleEnd = 0;
	  Lcd_Cursor (1, 1);
		for(i = 0; i < 16; i++)
	  {
			Lcd_DisplayChar('-');
		}
		Lcd_Cursor (2, 4);
		while(index < 7)
		{
			Lcd_DisplayChar(LOADING[index]);
			Delay4();
			index++;
		}
		i = 0;
		index = 0;
		for(i = 0; i < 3; i++)
	  {
			Lcd_DisplayChar(DotAndSpace[0]);
			Delay4();
		}
		i = 0;
		index = 1;
		Lcd_Cursor (3, 9);
		Lcd_DisplayChar(Percentage[0]);
		Lcd_DisplayChar(Percentage[10]);
		Lcd_Cursor (2, 11);
		for(i = 0; i < 3; i++)
	  {
			Lcd_DisplayChar(DotAndSpace[1]);
			DotsNumber = 0;
		}
		Delay4();
		while(index < 10)
		{
			Lcd_Cursor (3, 8);
			Lcd_DisplayChar(Percentage[index]);
			Lcd_Cursor (4, index + 3);
			Lcd_DisplayChar(LoadingBar[0]);
			if(DotsNumber == 0 && DidCycleEnd == 0)
			{
				Lcd_Cursor (2, 11);
				Lcd_DisplayChar(DotAndSpace[0]);
				DotsNumber = 1;
				DidCycleEnd = 1;
			}
			else if(DotsNumber == 1 && DidCycleEnd == 0)
			{
				Lcd_Cursor (2, 12);
				Lcd_DisplayChar(DotAndSpace[0]);
				DotsNumber = 2;
				DidCycleEnd = 1;
			}
			else if(DotsNumber == 2 && DidCycleEnd == 0)
			{
				Lcd_Cursor (2, 13);
				Lcd_DisplayChar(DotAndSpace[0]);
				DotsNumber = 3;
				DidCycleEnd = 1;
			}
			else if(DotsNumber == 3 && DidCycleEnd == 0)
			{
				Lcd_Cursor (2, 11);
				Lcd_DisplayChar(DotAndSpace[1]);
				Lcd_DisplayChar(DotAndSpace[1]);
				Lcd_DisplayChar(DotAndSpace[1]);
				DotsNumber = 0;
			}
			index++;
			DidCycleEnd = 0;
			Delay4();
		}
		Lcd_Cursor (3, 7);
		Lcd_DisplayChar(Percentage[1]);
		Lcd_DisplayChar(Percentage[0]);
		Lcd_Cursor (4, 13);
		Lcd_DisplayChar(LoadingBar[0]);
		Lcd_Cursor (2, 12);
		Lcd_DisplayChar(DotAndSpace[0]);
		Delay4();
		Lcd_DisplayChar(DotAndSpace[0]);
		Delay();
		
 }
 
 void LcdInitialize(void)
 {
   Delay();
   P2 = 0x83;
   LCD_E   = True;
   Delay2();
	 
   LCD_E   = False;
   Delay3();
	 
   LCD_E   = True;
   Delay2();
	 
   LCD_E   = False;
   Delay2();
	 
   LCD_E   = True;
   Delay2();
	 
   LCD_E   = False;
   Delay2();
	 
   LCD_DB4 = False;
   LCD_E   = True;
   Delay2();
		 
   LCD_E   = False;
   Delay2();
	 
   Lcd_SendCommand(LCD_CONFIG);     
   Lcd_SendCommand(LCD_CLEAR);      
   Lcd_SendCommand(LCD_DISPLAY_OFF);
   Lcd_SendCommand(LCD_DISPLAY_ON); 
   Lcd_SendCommand(LCD_ENTRY_MODE); 
   Lcd_SendCommand(LCD_CLEAR);   	 
 }
 
void main(void){
  LcdInitialize();
	LcdLoading();
  while(1) 
	{
		Lcd_DisplayScreen(Screen1);
		Delay4();
		Lcd_DisplayScreen(Screen2);
		Delay4();
		Lcd_DisplayScreen(Screen3);
		Delay4();
		Lcd_DisplayScreen(Screen4);
		Delay4();
		Lcd_DisplayScreen(Screen5);
		Delay4();
	}
}