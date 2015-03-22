#define GPJ2CON_0 (*(volatile unsigned long *)0xE0200280)
#define GPJ2DAT_0 (*(volatile unsigned long *)0xE0200284)

int main()
{
	GPJ2CON_0 = 0x00001111;
	GPJ2DAT_0 = 0;
	return 0;
}