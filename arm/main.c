#include "gpio.h"
#include "cpu.h"
#include "uart.h"

void mydelay(int input)
{
	volatile int count = input;
	while(count--);
}

int main()
{
	struct s5p_gpio *gpio_base = (struct s5p_gpio *)S5PV210_GPIO_BASE;
	gpio_base->gpj2.con = 0x00000011;
	while(1){
		gpio_base->gpj2.dat = 0;
		mydelay(100000);
		gpio_base->gpj2.dat = 0xf;
		mydelay(100000);
	}
	return 0;
}