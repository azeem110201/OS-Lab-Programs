#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void *square(int *num)
{
    int n = *num;
    printf("Thread Id is %lu\n\n", pthread_self());
    printf("PID is %d\n\n", getpid());
    printf("Square of given number %d is %d\n\n", n, (n * n));
}

int main()
{
    
    pthread_t thr_id;
    int rval,number;

    system("clear");

    printf("Enter the number to square \n");
    scanf("%d",&number);

     printf("Main Thread: Size of pthread is %d",sizeof(pthread_t));
     rval=pthread_create(&thr_id,NULL,(void *)square,number);
     if(rval==-1){
         //error/
     }
     prinf('Rval: %d',rval);
     pthread_join(thr_id,NULL);




}
