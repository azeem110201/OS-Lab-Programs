// Program to demonstrate basic thread operations
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void *square(int *a1)
{
    int a = *a1;
    printf("\n THRT:Thread task \t thread id is %lu", pthread_self());
    system("ps -l");
    printf("\n THRT: PID = %d \n", getpid());
    printf("\n squrare of %d is %d \n", a, (a * a));
}

int main()
{
    pthread_t thr_id;
    int rval, number, i;
    system("clear");

    printf("\n enter the number to square:\t");
    scanf("%d", &number);
    printf("\n MainThread: Sizeof pthread_t is %ld \n",
           sizeof(pthread_t));
    rval = pthread_create(&thr_id, NULL, (void *)square, &number);
    printf("\n MainThread: rval = %d \n", rval);
    printf("\n MainThread: Thread id = %lu \t process id = %d\n", thr_id, getpid());
    if (rval == -1)
    {
        perror("THRD-CR-ERR:");
        exit(1);
    }
    rval = pthread_join(thr_id, NULL);
}