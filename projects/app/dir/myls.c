#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define ERR(x) {perror(x);exit(errno);}

int count,i;
char obj_dir[NAME_MAX];
struct stat buf;
struct dirent **namelist;

int filter(const struct dirent *d)
{
	return 1;
}

int complex_print()
{
	char reset[NAME_MAX];
	strcpy(reset,obj_dir);
	count = scandir(obj_dir,&namelist,filter,alphasort);
	for(i=0;i<count;i++){
		strcpy(obj_dir,reset);
		strcat(obj_dir,"/");
		strcat(obj_dir,namelist[i]->d_name);
		if(stat(obj_dir,&buf) == 0)
			printf("%lo %ld %ld %ld %lld %s\n",(unsigned long)buf.st_mode,buf.st_nlink,(long)buf.st_uid,(long)buf.st_gid,(long long)buf.st_size,namelist[i]->d_name);
		else
			ERR("stat");
	}
	return 0;
}

int simple_print()
{
	count = scandir(obj_dir,&namelist,filter,alphasort);
	if(count == -1){
		ERR("scandir");
	}
	for(i=0;i<count;i++){
		printf("%s\n",namelist[i]->d_name);
	}

	return 0;
}


int main(int argc,char **argv)
{

	if(argv[1] == NULL){
		strcpy(obj_dir,".");
		simple_print();
	}
	else if(argv[1][1] == 'l' && argv[2] == NULL){
		strcpy(obj_dir,".");
		complex_print();
	}
	else if(argv[1][1] == 'l' && argv[2] != NULL){
		strcpy(obj_dir,argv[2]);
		complex_print();
	}
	else if(argc == 2){
		strcpy(obj_dir,argv[1]);
		simple_print();
	}
	else{
		printf("Usage: \n%s [-l] <dir>\n",argv[0]);exit(1);
	}

	return 0;
}








