#include <stdio.h>
//定义每个嫌疑犯的口供的真、假两种情况，供下面的组合配对使用 
#define A_TRUE A=0;B=1;C=1;D=1;
#define A_FALSE A=1;B=0;C=0;D=0;
#define B_TRUE A=0;B=0;C=1;D=0;
#define B_FALSE A=1;B=1;C=0;D=1;
#define C_TRUE A=1;B=0;C=0;D=1;
#define C_FALSE A=0;B=1;C=1;D=0;
#define D_TRUE B_TRUE
#define D_FALSE B_FALSE
#define OUTPUT printf("A=%d B=%d C=%d D=%d\n",A,B,C,D)


int A,B,C,D;

int isonly()
{
	
	int val = A+B+C+D; 
	if(val == 1) OUTPUT; //判断是否只有唯一一个人的值是1，如果是，则犯人确定
	A=0;B=0;C=0;D=0;
	return val;
}


int main()
{
	A=B=C=D=0;
	//在A，B，C，D四人中选出2人的口供为真，另外两人口供为假，并进行相应赋值(一共有6种组合)
	//A,B true
	A_TRUE B_TRUE C_FALSE D_FALSE
	isonly();
	//A,C true
	A_TRUE B_FALSE C_TRUE D_FALSE
	isonly();
	//A,D true
	A_TRUE B_FALSE C_FALSE D_TRUE
	isonly();
	//B,C true
	A_FALSE B_TRUE C_TRUE D_FALSE
	isonly();
	//B,D true
	A_FALSE B_TRUE C_FALSE D_TRUE
	isonly();
	//C,D true
	A_FALSE B_FALSE C_TRUE D_TRUE
	isonly();

	return 0;
}


