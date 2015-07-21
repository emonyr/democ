#include "gpio.h"
#include "cpu.h"
#include "uart.h"

#define GPJ2CON (*(volatile unsigned long *)0xE0200280)
#define GPJ2DAT (*(volatile unsigned long *)0xE0200284)

void mydelay(int input)
{
	volatile int count = input;
	while(count--);
}

void led_on(int ledno)
{
	GPJ2CON = (0x1 << ledno);
	GPJ2DAT = (0x0 << ledno);
}

void led_off(int ledno)
{
	GPJ2CON = (0x1 << ledno);
	GPJ2DAT = (0x1 << ledno);
}

int main()
{
	//uart_init();
	//ugets();

	while(1){
		led_on(0);
		mydelay(100000);
		led_off(0);
		mydelay(100000);
	}
	
	return 0;
}