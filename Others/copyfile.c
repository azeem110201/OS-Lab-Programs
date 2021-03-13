#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
    int fd1,fd2,n;
    char buffer[10];

    fd1=open(argv[1],O_RDONLY);
    fd2=open(argv[2],O_WRONLY|O_CREAT,0644);

    if(fd1<0 || fd2<0)
    {
        printf("Failed in opening the file \n");
        exit(1);
    }

    while (1)
    {
        n=read(fd1,buffer,1);
        if(n==0)
        break;
        write(fd2,buffer,1);
    }

    close(fd1);
    close(fd2);

    fd2=open(argv[2],O_RDONLY);

    while (1)
    {
        n=read(fd2,buffer,1);
        if(n==0)
        break;
        write(1,buffer,1);
    }
    close(fd2);
    
    
}

