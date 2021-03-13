#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
	int pid,rval;

	system("clear");

	printf(" Process ID is %d \t Parent Process ID is %d\n\n",getpid(),getppid());
	
	system("ps -l");

	printf("\n Program to demonstrate zombie process \n");

	pid=fork();

	if(pid==-1)
	{
		perror("FRK-ERR:");
		exit(1);
	}
        if(pid==0)//child process
	{
		printf("\n CHLD-PR: Process Id is %d \t Parent Process Id is %d \n\n",getpid(),getppid());
		system("ps -l");
		exit(0);
	}else{
		sleep(1);
		printf("\n PRNT-PR: Process Id is %d \t Parent Process Id is %d\n\n",getpid(),getppid());
		system("ps -l");
		printf("\n\n PRNT-PR: Child ID - the value returned by fork function is %d \n",pid);
		rval= wait(0);
		system("ps -l");
		printf("\n PRNT-PR: Id of child process terminated returned through WAIT function is %d \n",rval);
	}
}
