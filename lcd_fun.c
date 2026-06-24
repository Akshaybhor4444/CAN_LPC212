#include"lcd_header.h"

void lcd_config(void)
{
 IODIR0|= RS|RW|EN|DATA;       //configure LCD pins as output port
 /*send the commands*/
 lcd_cmd(0x38);                //2 line display,8 bits, 5*7 dots
 lcd_cmd(0x0E);                //dISPLAY ON cursor on
 lcd_cmd(0x01);                //clear the display
 lcd_cmd(0x80);                // force cursor from 1st row 1st column
 
}

void lcd_cmd(unsigned char c)
{ 
 IOCLR0=(0xFF<<15);              //clear the data lines P0.15 to P0.22
 IOSET0=(c<<15);                 //load the commands on data lines
 IOCLR0=RS;                      //RS=0 for command mode
 IOCLR0=RW;	                     //RW=0 for write mode
 IOSET0=EN;                      //EN=1    
 delay(10);
 IOCLR0=EN;						 //EN=0
}

void lcd_data(unsigned char d)
{ 
  IOCLR0=(0xFF<<15);              //clear the data lines
  IOSET0=(d<<15);				  //load the data 
  IOSET0=RS;                      //RS =1 for data mode
  IOCLR0=RW;
  IOSET0=EN;
  delay(10);
  IOCLR0=EN;
}

void lcd_str(unsigned char *ptr)
{ 
  while(*ptr != '\0')
  {
    lcd_data(*ptr);
	ptr++;
  }
}

void lcd_num(unsigned int num)
{
  if(num)
  {
   lcd_num(num/10);
   lcd_data(num%10+0X30);
  }
}																		

void delay(unsigned int a)
{ 
  unsigned int i,j;
  for(i=0;i<a;i++)
  for(j=0;j<6000;j++);
}
