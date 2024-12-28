#include <REGX52.H>
#include <INTRINS.H>

sbit K1 = P3^1;//????
sbit K2 = P3^0;//??????
sbit K3 = P3^2;//???????
sbit K4 = P3^3;//???????
sbit pulse = P2^0;//???????(PUL)
sbit direction = P2^2;//??????(DIR)
	
void Delay1ms(unsigned int xms);
void Delay500us();

void main()
{
    int h = 0;

    while(1)
	{
        if(K1 == 0)
		{
			Delay1ms(20);
            while(K1 == 0);
            Delay1ms(20);//??

            direction = ~direction;//??????	
		}

        if(K2 == 0)
		{
			Delay1ms(20);
            while(K2 == 0);
            Delay1ms(20);//??

			for(h = 0; h < 100; h++) //for??100?,??100???
			{
				pulse = 0;
				Delay500us();
				pulse = 1;
				Delay500us();
			}
        }

        if(K3 == 0)
		{
			Delay1ms(20);
            while(K3 == 0);
            Delay1ms(20);//??

			for(h = 0; h < 500; h++) //for??500?,??500???
			{
				pulse = 0;
				Delay500us();
				pulse = 1;
				Delay500us();
			}
        }

        if(K4 == 0)
		{
			Delay1ms(20);
            while(K4 == 0);
            Delay1ms(20);//??

			for(h = 0; h < 3000; h++) //for??3000?,??3000???
			{
				pulse = 0;
				Delay500us();
				pulse = 1;
				Delay500us();
			}
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

void Delay500us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}