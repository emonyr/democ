#ifndef UART_H
#define UART_H

/* baudrate rest value */
union br_rest {
	unsigned short	slot;		/* udivslot */
	unsigned char	value;		/* ufracval */
};

struct s5p_uart_bank {
	unsigned int	ulcon;
	unsigned int	ucon;
	unsigned int	ufcon;
	unsigned int	umcon;
	unsigned int	utrstat;
	unsigned int	uerstat;
	unsigned int	ufstat;
	unsigned int	umstat;
	unsigned char	utxh;
	unsigned char	res1[3];
	unsigned char	urxh;
	unsigned char	res2[3];
	unsigned int	ubrdiv;
	union br_rest	rest;
	unsigned char	res3[0x3d0];
};

static inline int s5p_uart_divslot(void)
{
	return 1;
}

struct s5p_uart {
	struct s5p_uart_bank uart0;
	struct s5p_uart_bank uart1;
	struct s5p_uart_bank uart2;
	struct s5p_uart_bank uart3;
};

void uart_init(void);

void uputc(char c);

void uputs(const char *str);


#endif
