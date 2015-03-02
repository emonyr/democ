#include <stdio.h>

int int_reverse(int input)
{
	int tmp;
	while(input){
		tmp = tmp*10 + input%10;
		input /= 10;
	}
	return tmp;
}

int main()
{
	int val;
	val = int_reverse(12345);
	printf("%d\n",val);
	return 0;	
}