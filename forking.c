#include "headers.h"
struct bg
{

	pid_t pid;
	char com[100];
};
struct bg task[10000];
int num_com;

void bg(){
	pid_t pid;
	int status;
	while((pid=waitpid(-1,&status,WNOHANG | WUNTRACED))>0)
	{
		if(WIFEXITED(status))
		{
			for(int i=0;i<num_com;++i)
			{
				if(task[i].pid==pid)
				{
					
					fprintf(stderr,"\nProcess %s with pid %d exited normally.\nPress [Enter]\n",task[i].com,pid);
					break;
				}
			}
		}
	}
}
void forking ( char** input,int s ){  
    pid_t pid;
	int status;
	// c[size1-bg]='\0';
	if((pid=fork())<0)
	{
		printf("ERROR: forking failed\n");
		return ;
	}
	if(pid==0)
	{
		setpgid(0,0);
		if(execvp(*input,input)<0)
		{
			printf("Invalid task\n");
			exit(0);
		}
		exit(0);

	}
	else
	{
		task[num_com].pid=pid;
		strcpy(task[num_com].com,input[0]);
		num_com++;
		if(input[s-1][0]=='&'){
			signal(SIGCHLD,bg);
    	}
		else{
			waitpid(pid,&status,0);
		}
	}
}