#define GPJ2CON_0 (*(volatile unsigned long *)0xE0200280)
#define GPJ2DAT_0 (*(volatile unsigned long *)0xE0200284)

void mydelay(int input)
{
	volatile int count = input;
	while(count--);
}

int main()
{
		GPJ2CON_0 = 0x00000011;
		
		while(1){
			GPJ2DAT_0 = 0;
			mydelay(100000);
			GPJ2DAT_0 = 0xf;
		}
	return 0;
}