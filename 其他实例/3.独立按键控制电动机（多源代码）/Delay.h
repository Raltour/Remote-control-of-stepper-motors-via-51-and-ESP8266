#include <INTRINS.H>

void Delay1ms(unsigned int xms);
void Delay500us();

sbit K1 = P3^1;//改变方向
sbit K2 = P3^0;//转动一个角度
sbit K3 = P3^2;//转动另一个角度
sbit K4 = P3^3;//再转动一个角度
sbit pulse = P2^0;//定义脉冲输出脚(PUL)
sbit direction = P2^2;//定义方向引脚(DIR)