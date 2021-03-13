// File Name : nrw.c
// Program to implement N Reader 1 writer using Message Passing. Here value of N=2
// First the writer process writes N messages and then reader processes read one each.
// Since Message Qs are used, when a message is read from the Q it is deleted i.e. why writer is writing multiple messages.
// Whenever there is an error in creation of resource i.e. shared memory,semaphore, message Qs or child process, all the resources created till
//then  are released.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>

int mutex;              // semaphore set id - for reader processes to access rdr_cnt.
int wrt_mutex;          // semaphore set id - for reader and writer for accessing shared resource.
struct sembuf sup, sdn; // used with semop function - sup to up the semaphore, sdn to down the semaphore
union semun
{
    int val;
} a;
int shmid;    // shared memory id
int *rdr_cnt; // shared memory pointer
int msqid;    // Msg. Q id.
struct msg
{
    long id;
    char msg[10];
} rbuf, wbuf;
void semup(int semid) // signal operation
{
    sup.sem_num = 0;
    sup.sem_op = 1;
    sup.sem_flg = 0;
    semop(semid, &sup, 1);
}
void semdown(int semid) // wait operation
{
    sdn.sem_num = 0;
    sdn.sem_op = -1;
    sdn.sem_flg = 0;
    semop(semid, &sdn, 1);
}
void Readerp(int id, int msgid)
{
    int rval;
    semdown(mutex); // Incrementing reader count
    (*rdr_cnt)++;
    if ((*rdr_cnt) == 1)
        semdown(wrt_mutex);
    printf("\n RP:RD-ID=[%d] incrementing \tRD_CNT =%d\n", id, *rdr_cnt);
    semup(mutex);
    rval = msgrcv(msqid, &rbuf, sizeof(rbuf), msgid, 0);
    if (rval != -1)
        printf("\n RP: RD-ID- %d: MESSAGE READ is %s\n", id, rbuf.msg);
    semdown(mutex); // Decrementing reader count
    (*rdr_cnt)--;
    printf("\n RP:RD-ID=[%d] decrementing \tRD_CNT =%d\n", id, *rdr_cnt);
    if ((*rdr_cnt) == 0)
        semup(wrt_mutex);
    semup(mutex);
}
void Writerp(int id, int msgid)
{
    int rval, n_msgs, i;
    semdown(wrt_mutex);
    printf("\n WrP: Wrp-ID - %d : is executing in its Critical Section\n", id);
    printf("\n Enter the number of messages to write : \t");
    scanf("%d", &n_msgs);
    for (i = 1; i <= n_msgs; i++) // more than 1 msg is written since when msg is read from Q it is deleted
    {
        printf("\n WrP: Enter the data to write to Q:\t");
        scanf("%s", wbuf.msg);
        wbuf.id = msgid;
        rval = msgsnd(msqid, &wbuf, sizeof(wbuf), 0);
        if (rval == 0)
            printf("\n WP: DATA WRITTEN to Q by writer id =%d\n", id);
        else
            perror("MSG-Q-WR-ERR");
    }
    printf("\n WrP: WrP-ID - %d, leaving its Critical Section \n", id);
    semup(wrt_mutex);
}
int main()
{
    int pid, rval, msgid;
    system("clear");
    // creating shared memory segment to hold string data of size 10bytes;
    shmid = shmget((key_t)83, 10, IPC_CREAT | 0666);  //Please give your roll number as key value
    if (shmid == -1)
    {
        perror("SHM_CRE_ERR:");
        exit(1);
    }
    rdr_cnt = (int *)shmat(shmid, 0, 0); // shared memory attached to process address space.
    if (rdr_cnt == NULL)
    {
        perror("SHM_ATTACH_ERR:");
        shmctl(shmid, IPC_RMID, 0);
        exit(1);
    }
    system("ipcs -m");                           // diplaying status of shared memory created
    msqid = msgget((key_t)10, IPC_CREAT | 0666); // creating Message Queue
    if (msqid == -1)
    {
        perror("MsgQ_CREAT_ERR:");
        shmdt(rdr_cnt);
        shmctl(shmid, IPC_RMID, 0);
        exit(1);
    }
    system("ipcs -q");                                                                 // displaying the message Q created status
    printf("\n Enter the MSG-ID to be used for reading and writing messages to Q:\t"); // global msg id used to send and recv. msgs.
    scanf("%d", &msgid);
    // creating binary semaphore wrt_mutex to access rdr_cnt.Initial value set to 1.
    mutex = semget((key_t)83, 1, IPC_CREAT | 0666); // use your roll number for key_t value
    if (mutex == -1)
    {
        perror("SEM_GET_ERR:");
        shmdt(shmid, 0, 0);
        shmctl(shmid, IPC_RMID, 0);
        msgctl(msqid, IPC_RMID, 0);
        exit(1);
    }
    system("ipcs -s"); // displaying status of semaphore element created
    // printing default value of semaphore element
    printf("\n default value of semaphore element is %d \n", semctl(mutex, 0, GETVAL, 0));
    // setting the value of semaphore element to intial value 1.
    a.val = 1;
    rval = semctl(mutex, 0, SETVAL, a);
    if (rval != -1)
        printf("\n value of semaphore element set is %d \n",
               semctl(mutex, 0, GETVAL, 0));
    else
    {
        perror("SEM_SETVAL_ERR:");
        shmdt(rdr_cnt);
        shmctl(shmid, IPC_RMID, 0);
        msgctl(msqid, IPC_RMID, 0);
        semctl(mutex, 0, IPC_RMID, 0);
        exit(1);
    }
    // creating binary semaphore wrt_mutex to access shared resource. Initial value set to 1.
    wrt_mutex = semget((key_t)84, 1, IPC_CREAT | 0666); // use your (roll number + 1) for key_t value
    if (wrt_mutex == -1)
    {
        perror("SEM_GET_ERR:");
        shmdt(shmid, 0, 0);
        shmctl(shmid, IPC_RMID, 0);
        msgctl(msqid, IPC_RMID, 0);
        semctl(mutex, IPC_RMID, 0);
        exit(1);
    }
    system("ipcs -s"); // displaying status of semaphore element created
    sleep(2);          // done just to see display
    // printing default value of semaphore element
    printf("\n default value of semaphore element is %d \n", semctl(wrt_mutex, 0, GETVAL, 0));
    // setting the value of semaphore element to intial value 1.
    a.val = 1;
    rval = semctl(wrt_mutex, 0, SETVAL, a);
    if (rval != -1)
        printf("\n value of semaphore element set is %d \n",
               semctl(wrt_mutex, 0, GETVAL, 0));
    else
    {
        perror("SEM_SETVAL_ERR:");
        shmdt(rdr_cnt);
        shmctl(shmid, IPC_RMID, 0);
        msgctl(msqid, IPC_RMID, 0);
        semctl(mutex, IPC_RMID, 0);
        semctl(wrt_mutex, IPC_RMID, 0);
    }
    *rdr_cnt = 0; // setting the value of reader count to 0
    system("clear");
    // executing fork system call to create reader and writer processes
    pid = fork();
    if (pid == -1)
    {
        perror("Fork -ERR:");
        shmdt(rdr_cnt);
        shmctl(shmid, IPC_RMID, 0);
        msgctl(msqid, IPC_RMID, 0);
        semctl(mutex, 0, IPC_RMID, 0);
        semctl(wrt_mutex, 0, IPC_RMID, 0);
        exit(1);
    }
    if (pid == 0) // reader process
    {
        sleep(1);
        Readerp(1, msgid);
        exit(1);
    }
    else
    {
        pid = fork();
        if (pid != -1)
            if (pid == 0) // reader process
            {
                sleep(1);
                Readerp(2, msgid);
                exit(1);
            }
            else
            {
                Writerp(2, msgid);
                wait(0); // wait till all child processes terminate.
                printf("\n All resources being released \n");
                shmdt(rdr_cnt);
                shmctl(shmid, IPC_RMID, 0);
                msgctl(msqid, IPC_RMID, 0);
                semctl(mutex, 0, IPC_RMID, 0);
                system("ipcs");
            }
        else
        {
            Writerp(2, msgid);
            wait(0); // wait till all child processes terminate.
            printf("\n All resources being released \n");
            shmdt(rdr_cnt);
            shmctl(shmid, IPC_RMID, 0);
            msgctl(msqid, IPC_RMID, 0);
            semctl(mutex, 0, IPC_RMID, 0);
            semctl(wrt_mutex, 0, IPC_RMID, 0);
        }
    }
}