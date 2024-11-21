#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<wait.h>
#include<sys/types.h>
void handle_sigup(int sig)
{
	printf("Child received SIGHUP\n");
}
void handle_sigint(int sig)
{
	printf("Child received SIGINT\n");
}
void handle_sigquit(int sig)
{
	printf("Child received SIGQUIT\n");
	exit (0);
}
int main()
{
	pid_t pid=fork();
	if(pid<0)
	{
		printf("fork failed");
		exit (0);
	}
	if (pid==0)
	{
		signal(SIGHUP,handle_sigup);
		signal(SIGINT,handle_sigint);
		signal(SIGQUIT,handle_sigquit);
		while(1)
		{
			pause();
		}
	}
		else
		{
			for (int i=0;i<5;i++)
			{
				if(i % 2==0)
				{
					printf("Parent:Sending SIGHUP\n");
					kill(pid,SIGHUP);
				}
				else
				{
					printf("Parent:Sending SIGINT\n");
					kill(pid,SIGINT);
				}
				sleep(1);
			}
			printf("Parent:Sending SIGQUIT\n");
			kill(pid,SIGQUIT);
			wait(NULL);
			printf("My papa has kill me!");
		}
		return 0;
}		
