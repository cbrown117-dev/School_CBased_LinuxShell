 /*
 *chris Brown
 * sevrc
 * Project: 4
 */

// I copied existing code of mine that we made throughout this semester and used that
// the .h file has the code I took from
// and of course geeks for geeks .com
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

#include "redirect.h"
#include "queue.h"

int main(int argc, char **argv){
	pid_t pid;

	/* set up time */
	struct tm* ptr;
	time_t lt;
	lt = time(NULL);

	int numCores, index = 0, jobs = 0;

	if(argc < 2){  printf("need more arguents <program to run>\n");  exit(-1); }

	numCores = atoi(argv[1]);
	hyLog hy[numCores];

	queue *q = queue_init(numCores); /* init queue */
	
	printf("Enter command> ");
	char ch[150];
	fgets(ch,150,stdin);
	
	
	while( strcmp(ch, "quit\n") != 0 ){
		/*breaks down input into an array of strings */        
		char *commands[10];
		char cmd[50];
		char *pid_name;
		char *token = strtok(ch, " ");

		strcpy(cmd, token);
		pid_name = cmd;

		while(token != NULL){
			commands[index] = token; 
			token  = strtok(NULL," ");
			index++;
		}

		commands[index] = NULL;

		printf("commands[0] = %s commands[1] = %s", commands[0], commands[1]);

		/* checks input for commands to do things */
		if( strcmp(commands[0], "submit") == 0 ){
			printf("made it inside submit\n");
			int check;
			if( check = queue_insert(q, commands[1]) < 0 )
				printf("queue full type showobs and when there is a spot open try again\n");
			else{
				//fork it and add to the queue
				printf("made it past insert\n");
				jobs++;
				printf("hy.job_ids = %d\n", hy[jobs-1].job_ids = jobs-1);
				printf("hy.name = %s\n", hy[jobs-1].name = commands[1]);
				ptr = localtime(NULL);
				char *t = asctime(ptr);
				printf("t = %s\n", t);
				printf("start = %s\n",(hy[jobs-1].start = t));
				printf("status is %s\n", hy[jobs-1].status = "running");

				hy[jobs-1].job_ids = jobs-1;
				hy[jobs-1].name = commands[1];  
				hy[jobs-1].start = t;
				hy[jobs-1].status = "running";

				/* execvp it in redirect.h */
				redirect(index, commands, jobs-1, hy);
				//printf here submitted job
				
			}

			fflush(stdin);
		}

		if( strcmp(commands[0], "showjobs") ==0 ){
			if(jobs != 0){
				int i;
				printf("jobid\tcommands\t\tstatus\n");
				for(i=0;i<jobs-1;i++){
					
				}
			}
		}
			
		if( strcmp(commands[0], "submithistory\n") == 0 ){
			
		}	
	
		char check[150];
		printf("Enter command> ");
		fflush(stdin);
		fflush(stdout);
		fgets(check, 150, stdin);
		strcpy(ch, check);
		index = 0;
	}

return 0;
}
