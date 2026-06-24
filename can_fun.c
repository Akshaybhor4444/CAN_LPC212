/*pgm to transmit a char using CAN protocol*/

#include "lcd_fun.c"


// checking the git 



unsigned int MSG[10];

void can_config(void)
{
  VPBDIV=2;	  //config can clock reg wewant  CANclk=10Mz   
  PINSEL1|=(1<<14)|(1<<16)|(1<<18);
  PINSEL1&=~((1<<15)|(1<<17)|(1<<19)); // config can port P0.23, P0.24,P0.25


  //bit ratre prescalar

  /*BRP=2+1 ,TSEG1=15+1,TSEG2=3+1 */	 //in mod reg we disable can and load some value and again emable can 

  C2MOD=(1<<0);//CAN DISABE
  C2BTR=(3<<20)|(15<<16)|(2<<0);// TSEG1,  TSEG2,BRP(ie 10Mz),(16(TSEG1)+4(TSEG2)+1(sync seg)=21Tq) in limit 
  C2MOD=0;//ENABLE CAN

	//CAN2 TX

  C1MOD=(1<<0);//CAN DISABE
  C1BTR=(3<<20)|(15<<16)|(2<<0);
  C1MOD=0;//ENABLE CAN

	//CAN1 RX
 }

   void can_tx(unsigned int d)
{
 while(!(C2GSR&(1<<2)));//TBS IS EMPTY OR NOT  tbs=1.. CHECK TX BUFFER empty or not 
 C2TID1=0x27;// LOAD THE ID					 
 C2TFI1=(1<<19);//FRAME CONTROL BITS DLC=0100 -- 4 butes [19,16],RTR=0,IDE=0
 C2TDA1=d;//DATA
 C2CMR=(1<<0)|(1<<5);//COMAD VALUES QUEUED TX is tx is ready , TX BUFFER 1
 while(!(C2GSR&(1<<3)));//CHECK TX COMPLETE OR NOT
}


unsigned int can_rx(void)
{
 while((C1GSR&(1<<0)));//CHECK RBR RX DATA OR NOT
 MSG[0]=C1RID;//LOAD THE ID TO VARIABLE
 MSG[1]=C1RDA; // load the data to variable
 C1CMR=(1<<2);//RELEASE RBR FOR NEXT RX	, ie clear rbr for nrxt rx
 return MSG[1];  
}







