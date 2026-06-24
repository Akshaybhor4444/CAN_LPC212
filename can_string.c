#include<lpc21xx.h>
	#include "CAN_fun.c"
	
	unsigned int MSG[10];

//	void can_config(void);
//	void can_tx(unsigned int d1);
//    unsigned  int can_rx(void);

	int main()
	{
	 unsigned char s[20]="AKSHAY BHOR";
		unsigned int b,i;

	 lcd_config();
	 can_config();
	
	for(i=0;s[i]!='\0';i++)
	 {
	 can_tx(s[i]);
	 b=can_rx();
	 lcd_data(b);
	  }
	 lcd_cmd(0xC0);
	 lcd_num(MSG[1]);
	}
