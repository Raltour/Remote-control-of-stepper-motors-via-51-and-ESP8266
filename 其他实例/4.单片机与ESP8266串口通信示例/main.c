//网址：https://www.cnblogs.com/caojun97/p/16841634.html

/*-----------------------------------------------------------------------------
* 实验说明     : 单片机串口接收数据控制灯亮灭
* 连接方式     : 
* 注    意     : 该试验使用的晶振是11.0592
*******************************************************************************/

#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint  unsigned int

uchar PuZh[20] = "This is ok";

//--定义使用的IO--//
sbit LED=P2^0;

void Delay_1ms(uint i)//1ms延时
{
  	uchar x,j;
  	for(j=0;j<i;j++)
    	for(x=0;x<=148;x++);
}

void Com_Int(void) interrupt 4
{
	uchar i;
  	uchar receive_data;
  	EA = 0;//总中断置零，防止再有其他输入导致再次进行串口中断
  	if(RI == 1) //当硬件接收到一个数据时，RI会置位
	{ 		
		RI = 0;//RI置位后要手动归位
		receive_data = SBUF;//RXD将接收到的数据传给移位寄存器，SBUF记录接收到的数据
		if(receive_data == '1')//这里表示SBUF接收到了unsigned char类型的数据，大小为1字节
		{
			LED =0;//接收到字符'1'亮灯
		}
		else
		{
			LED =1; //其他情况灯灭
		}
	}

	for(i=0; i<20; i++)
	{
		SBUF = PuZh[i];   //将要发送的数据放入到发送寄存器
		while(!TI);       //等待发送数据完成，TI变为1表示发送完成
		TI=0;		  //清除发送完成标志位
		Delay_1ms(1);
	}
	EA = 1;//回复总中断，回复串口中断
}

void UsartConfiguration()
{	
	SCON=0X50;			//设置为工作方式1,8位数据，可变波特率
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X00;			//波特率不加倍
	TH1=0XFd;		    //计数器初始值设置，9600@11.0592MHz
	TL1=0XFd;
	TR1=1;			    //打开计数器
	ES = 1;             //开串口中断
  	EA = 1;             //开总中断
}
	
void main()
{
	UsartConfiguration();//初始化串口
	while(1);	
}