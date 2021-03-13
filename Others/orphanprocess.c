#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int pid;
	system("clear");
	printf(" Process ID is %d \t Parent Process ID is %d\n\n",getpid(),getppid());
	
	system("ps -l");

	printf("\n Program to demonstrate orphan process \n");

	pid=fork();
	if(pid==-1)
	{
		perror("FRK-ERR:");
		exit(1);
	}
        if(pid==0)//child process
	{
		printf("\n CHLD-PR: Process Id is %d \t Parent Process Id is %d \n\n",getpid(),getppid());
		system("ps -l");//child goes to sleep meanwhile parent terminates making child process orphan
		sleep(10);
		printf("\n CHLD:PR: Process Id is %d \t Parent Process Id is %d \n\n",getpid(),getppid());
		system("ps -l");
	}else{
		sleep(1);
		printf("\n PARENT-PR: Process Id is %d \t Parent Process Id is %d\n\n",getpid(),getppid());
		system("ps -l");
	}
}
