#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{

	int n,fd,fd1;
	char buff[50];
	fd=open("test.txt",O_RDONLY);
	printf("the fd of the newly created read file is %d",fd);
	n=read(fd ,buff,10);
	fd1=open("target.txt", O_CREAT | O_WRONLY,0642);
	write(fd1,buff,n);
}
