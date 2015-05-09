#ifndef IO_H
#define IO_H

#define readl(a) (*(volatile unsigned long *)(a))
#define writel(v,a) ((*(volatile unsigned long *)(a)) = v)
#define __REG(a) (*(volatile unsigned long *)(a))




#endif
