    #include<lpc21xx.h>
	#include "CAN_fun.c"
	
	int main()
	{
	 unsigned char b;

	 lcd_config();
	 can_config();

	 can_tx('S');
	 
	 b=can_rx();
	 lcd_data(b);

	 lcd_cmd(0xC0);

	 lcd_num(MSG[0]);// id will be seen 
	}
