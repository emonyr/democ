#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a = 5;
	int *b;
	b = malloc(sizeof(a));
	*b = (a & 0x1);
	*b >>= 1;
	printf("%d\n",*b);

	return 0;
}