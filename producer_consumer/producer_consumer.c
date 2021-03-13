// File Name : pc.c
// Program to implement Producer Consumer Problem using Shared Memory
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>

int semid;
int shmid;
char *shmptr;
struct sembuf sup, sdn;
void semup(int process_id)
{
    semop(semid, &sup, 1);
    printf("\n %d process has signals the semaphore \n", process_id);
}
void semdown(int process_id)
{
    semop(semid, &sdn, 1);
    printf("\n %d process downs the semaphore \n", process_id);
}
union semun
{
    int val;
} a;
int main()
{
    int pid, rval;
    char pbuf[10], cbuf[10];
    system("clear");
    // creating shared memory segment to hold string data of size 10 bytes;
    shmid = shmget((key_t)83, 10, IPC_CREAT | 0666); // please give your roll number as key value 
    
    if (shmid == -1)
    {
        perror("SHM_CRE_ERR:");
        exit(1);
    }
    shmptr = (char *)shmat(shmid, 0, 0);

    if (shmptr == NULL)
    {
        perror("SHM_ATTACH_ERR:");
        shmctl(shmid, IPC_RMID, 0);
        exit(1);
    }
    // diplaying status of shared memory created
    system("ipcs -m");
    // creating binary semaphore. Initial value set to 1.
    semid = semget((key_t)10, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("SEM_GET_ERR:");
        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, 0);
        exit(1);
    }
    // displaying status of semaphore element created
    system("ipcs -s");
    // printing default value of semaphore element
    printf("\n default value of semaphore element is %d \n", semctl(semid, 0, GETVAL, 0));
    // setting the value of semaphore element to intial value 1.
    a.val = 1;
    rval = semctl(semid, 0, SETVAL, a);
    if (rval != -1)
        printf("\n value of semaphore element set is %d\n", semctl(semid, 0, GETVAL, 0));
    else
    {
        perror("SEM_SETVAL_ERR:");
        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, 0);
        semctl(semid, 0, IPC_RMID, 0);
        exit(1);
    }
    sup.sem_num = 0;
    sup.sem_op = 1;
    sup.sem_flg = 0;
    sdn.sem_num = 0;
    sdn.sem_op = -1;
    sdn.sem_flg = 0;
    sleep(5);
    // executing fork system call to create child process
    // child process is producer, parent process is consumer.
    pid = fork();
    if (pid == -1)
    {
        perror("ForkERR:");
        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, 0);
        semctl(semid, 0, IPC_RMID, 0);
        exit(1);
    }
    if (pid == 0) // producer process
    {
        semdown(getpid());
        printf("\n PRD: process id is %d\n\n", getpid());
        printf("\n PRD: Enter the string to write to shared memory :\t");
        scanf("%s", pbuf);
        printf("\n Prd: writing to shared memory:\n");
        strcpy(shmptr, pbuf);
        printf("\n Prd: EXITING shared memory:\n");
        semup(getpid());
        exit(1);
    }
    else
    {
        sleep(1);
        semdown(getpid());
        printf("\n CRD: process id is %d\n\n", getpid());
        printf("\n CRD: Consumer Process reading data from sharedmemory:\n");
        strcpy(cbuf, shmptr);
        printf("\n CRD: exiting shared memory:\n");
        semup(getpid());
        printf("\n CRD: - Data Read from Shared Memory is %s\n", cbuf);
        wait(0);
        printf("\n All resources being released \n");
        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, 0);
        semctl(semid, 0, IPC_RMID, 0);
    }
}