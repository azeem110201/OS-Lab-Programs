#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    int pid, rval;
    system("clear");
    printf("\nProcess Id is %d and Parent Process Id is %d", getpid(), getppid());

    printf("\nProgram to demonstrate Zombie Process\n");

    pid = fork();

    if (pid == -1)
    {
        perror("FORK-ERR");
        exit(1);
    }

    if (pid == 0) //child process
    {
        printf("\nCHILD PR: Process Id is %d \t Parent Process Id %d", getpid(), getppid());
        exit(0);
    }
    else
    {
        printf("\nPARENT PR:Process Id is %d \t Parent Process Id is %d", getpid(), getppid());
        printf("Parent Pr:Value returned by fork function in %d", pid);
        system("ps -l");
        rval = wait(0);
        system("ps -l");
        printf("\n PRNT-PR: Id of child process terminated returned through WAIT function is %d \n", rval);
    }
}
