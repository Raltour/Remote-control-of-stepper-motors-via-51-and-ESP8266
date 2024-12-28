#include <INTRINS.H>
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