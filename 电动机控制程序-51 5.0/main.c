#include <REGX52.H>
#include <INTRINS.H>


sbit K1 = P3^1;//改变方向
sbit K2 = P3^0;//转动一个角度
sbit K3 = P3^2;//转动另一个角度
sbit K4 = P3^3;//再转动一个角度
sbit pulse = P2^0;//定义脉冲输出脚(PUL)
sbit direction = P2^2;//定义方向引脚(DIR)
int speed = 7;//电动机初始旋转速度
int mode=0;//电机启普发生器

void MotorControl(unsigned char Signal, int *p);
void Delay100us(unsigned int hunus);
void UART_Init();
void SendBytes(int num);
void KeyControl(int * p);
void Delay1ms(unsigned int xms);


//初始化串口通信以及计时器	//9600@11.0592MHz
void UART_Init() {
	SCON=0X50;			//设置为工作方式1,8位数据，可变波特率
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X00;			//波特率不加倍
	TH1=0XFd;		    //计数器初始值设置
	TL1=0XFd;
	TR1=1;			    //打开计数器
	ES = 1;             //开串口中断
  	EA = 1;             //开总中断
}


void main() {
    UART_Init();//初始化定时器以及串口通信的参数
    
    while(1)
    {
        KeyControl(&speed);
        Delay100us(1000);
    }
}


//串口中断函数，接收到数据后跳转到此处运行
void UART_Routine()  interrupt 4    {
    unsigned char Signal;
    EA = 0;
	if (RI ==  1) {
        RI = 0;
        Signal = SBUF;
        MotorControl(Signal, &speed);
    }
    EA = 1;
}


/*这是电动机的控制代码，通过接受参数Signal对步进电机的转动进行控制。
若 Signal == 0x09则转换电动机的旋转方向；
否则根据Signal的大小来转一定角度*/
void MotorControl(unsigned char Signal, int *p) {
	int h = 0;
	int num = 0;

	switch(Signal) {
		case 0x01:num = 100;break;
		case 0x02:num = 500;break;
        case 0x07:(*p)++;SendBytes(*p);break;//减慢一档速度
        case 0x08:(*p)--;SendBytes(*p);break;//加快一档速度
        case 0x09:direction = ~direction;break;//引脚状态取反,转换电动机旋转方向
	}

    //发送总计num个脉冲，频率为1000Hz
	for(h = 0; h < num; h++) {
			pulse = 0;
			Delay100us(*p);
			pulse = 1;
			Delay100us(*p);
		}
}


//@11.0592MHz//用于控制脉冲的频率，进而控制电动机的转速
void Delay100us(unsigned int hunus) {
	unsigned char i;
	while(hunus) {
		_nop_();
		i = 43;
		while (--i);
		hunus--;
	}
}


void SendBytes(int num) {
    SBUF = num;
    while (!TI);
    TI = 0;
}


void KeyControl(int * p) {
    unsigned char Signal;

    if(K1 == 0)
	{
		Delay1ms(20);
        while(K1 == 0);
        Delay1ms(20);//消震

        Signal = 0x09;//引脚状态取反	
	}

    if(K2 == 0)
	{
		Delay1ms(20);
        while(K2 == 0);
        Delay1ms(20);//消震

		Signal = 0x01;
    }

    if(K3 == 0)
	{
		Delay1ms(20);
        while(K3 == 0);
        Delay1ms(20);//消震

		Signal = 0x02;
    }

    MotorControl(Signal, &speed);
    Signal = 0;

    if(K4 == 0)
	{
		Delay1ms(20);
        while(K4 == 0);
        Delay1ms(20);//消震
        mode=(mode+1)%2;
        while (mode==1){
            pulse = 0;
			Delay100us(*p);
			pulse = 1;
			Delay100us(*p);
            KeyControl(&speed);
        }
    }
}

void Delay1ms(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;

    while(xms)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        } while (--i);   
        xms--;
    }
}