#include<unistd.h>
int main()
{
	int n;
	char bff[30];
	n=read(0,bff,10);
	write(1,bff,n);
}
