#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int pid;
    system("clear");
    printf("\nProcess Id is %d and Parent Process Id is %d", getpid(), getppid());

    printf("\nProgram to demonstrate Orphan Process\n");

    pid = fork();

    if (pid == -1)
    {
        perror("FORK-ERR");
        exit(1);
    }

    if (pid == 0) //child process
    {
        printf("\nCHILD PR: Process Id is %d \t Parent Process Id %d", getpid(), getppid());
        sleep(5); //child sleeps while parent terminates making child orphan
        printf("\nCHILD PR: Process Id is %d \t Parent Process Id %d", getpid(), getppid());
    }
    else
    {
        sleep(1);
        printf("\nPARENT PR:Process Id is %d \t Parent Process Id is %d", getpid(), getppid());
    }
}