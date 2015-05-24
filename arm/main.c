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
	uart_init();
	ugets();

	return 0;
}