#include <REGX52.H>
#include <Delay.h>

void main()
{
    int h = 0;

    while(1)
	{
        if(K1 == 0)
		{
			Delay1ms(20);
            while(K1 == 0);
            Delay1ms(20);//消震

            direction = ~direction;//引脚状态取反	
		}

        if(K2 == 0)
		{
			Delay1ms(20);
            while(K2 == 0);
            Delay1ms(20);//消震

			for(h = 0; h < 100; h++) //for循环100次，发送100个脉冲
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
            Delay1ms(20);//消震

			for(h = 0; h < 500; h++) //for循环500次，发送500个脉冲
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
            Delay1ms(20);//消震

			for(h = 0; h < 3000; h++) //for循环3000次，发送3000个脉冲
			{
				pulse = 0;
				Delay500us();
				pulse = 1;
				Delay500us();
			}
        }
    }
}