#ifndef IO_H
#define IO_H

#define __REG(a) (*(volatile unsigned int *)(a))

#define readl(a) (*(volatile unsigned long *)(a))
#define readb(a) (*(volatile unsigned char *)(a))
#define readw(a) (*(volatile unsigned short *)(a))

#define writel(v,a) ((*(volatile unsigned long *)(a)) = v)
#define writeb(v,a) ((*(volatile unsigned char *)(a)) = v)
#define writew(v,a) ((*(volatile unsigned short *)(a)) = v)



#endif
