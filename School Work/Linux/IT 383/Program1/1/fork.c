#include "sys/types.h"
#include "stdio.h"
#include "unistd.h"

int main()
{
	pid_t pid;
	pid = fork();
	//fork a child process
	printf("pid = %d\n",pid);
	if(pid<0)
	{
		fprintf(stderr, "Fork failed");
		return -1;
	}
	else if(pid ==0)//child process
	{
		execlp("/bin/ls","ls",NULL);
	}
	else //parent process
	{
		wait(NULL);
		printf("child complete\n");
	}
	return 0;
}
