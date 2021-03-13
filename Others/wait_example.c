#include<sys/types.h>
#include<unistd.h>   
#include<stdio.h>
#include<wait.h>
int main()   
{                  
	pid_t p; 
	printf("Before fork\n"); 
	p=fork(); 
	if(p<0)
	{       
		printf("error");
	}
	else if(p==0)//child process
	{ 
	  	printf("I'm child having id %d\n\n",getpid());
		printf("My parent id is %d\n\n",getppid());   
	}else{  
	        wait(NULL);	
		printf("I'm parent with id %d\n\n",getpid()); 
		printf("My childs id is %d\n\n",p);
	}
	printf("Common\n\n");
}
 
