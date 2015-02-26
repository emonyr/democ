#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXVAL 100

int getrandom()
{
	//此函数用于产生随机数
	return (random()+time(NULL))%MAXVAL + 1; //加上时间，使得每次得到的随机数不一样
}


int main()
{
	int chance = 8;
	int input,a;
	a = getrandom(); //获得随机数
	//循环直到chance小于0
	while(chance--)
	{
		printf("#You have %d chance left to guess\n",chance);
		printf("#Please input a number between 1 ~ %d\n",MAXVAL);
		scanf("%d",&input);
		//输入的数字与前面获得的随机数a进行比较
		if(input < a)
			printf("Wrong answer , too small\n\n");
		else if(input > a)			
			printf("Wrong answer , too big\n\n");
		else
		{	printf("Bingo!\n"); //表示猜对了
			break;
		}
	}
	if(chance < 0)
		printf("Sorry,you failed in 8 chances\n"); //chance小于0，说明用完8次机会都没猜对
	printf("The answer is %d\n",a);
	return 0;
}
