#include <stdio.h>
#include <errno.h>

ifdef __DEBUG__
#define ERR(x) do{perror(x);exit(errno);} while(0)
else
#define ERR(x) do{} while(0)
endif
