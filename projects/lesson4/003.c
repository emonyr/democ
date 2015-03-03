#include <stdio.h>


char *perm_convert(int input)
{
	int i = 9;
	static char output[9];
	
	while(i > 0){
		if(input & (1 << (i-1))){	
			switch(i%3){
				case 0:
				output[9-i] = 'r';
				break;
				case 2:
				output[9-i] = 'w';
				break;
				case 1:
				output[9-i] = 'x';
				break;
			}
		}
		else 
			output[9-i] = '-';
		i--;
	}
	output[9] = '\0';
	return output;
}

int main()
{
	char *p;
	p = perm_convert(0744);
	printf("%s\n",p);
	return 0;
}