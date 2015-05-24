#include "cpu.h"
#include "uart.h"
#include "io.h"
#include "gpio.h"


void uart_init(void)
{
	struct s5p_gpio *gpio_base = (struct s5p_gpio *)S5PV210_GPIO_BASE;
	struct s5pv2xx_uart *uart_base = (struct s5pv2xx_uart *)S5PV210_UART_BASE;
	unsigned int var;
	
	//设置通用总线为UART功能
	var = readl(&gpio_base->gpa0.con);
	var &= ~(0xff<<0);
	var |= 0x22;
	writel(var,&gpio_base->gpa0.con);

	//设置UART寄存器
	__REG(&uart_base->ulcon) = 0x3;
	__REG(&uart_base->ucon) = 0x5;
	__REG(&uart_base->ubrdiv) = 35;
	__REG(&uart_base->udivslot) = 0x80;
	
}


void uputc(char c)
{
	struct s5pv2xx_uart *uart_base = (struct s5pv2xx_uart *)S5PV210_UART_BASE;

	while(!(__REG(&uart_base->utrstat) & (0x1<<2)));
	
	__REG(&uart_base->utxh) = c;

}


void uputs(const char *str)
{

	while(*str){
		uputc(*str);
		str++;
	}

}

void ugetc(void)
{
	char c;
	struct s5pv2xx_uart *uart_base = (struct s5pv2xx_uart *)S5PV210_UART_BASE;
	while(!(__REG(&uart_base->utrstat) & (0x1<<0)));

	c = readb(&uart_base->urxh);

	uputc(c);	//回显
}

void ugets(void)
{
	struct s5pv2xx_uart *uart_base = (struct s5pv2xx_uart *)S5PV210_UART_BASE;

	uputs("uputs:\n");
	while(!(__REG(&uart_base->utrstat) & (0x1<<0)));
	ugetc();
	
	while(readb(&uart_base->urxh) != '0'){
		ugetc();
	}
	uputs("exit uputs\n");
}





