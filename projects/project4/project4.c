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
	hyLog list[numCores];
	hyLog  hy[10];

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

		int len = strlen(commands[0]);
		if(commands[0][len-1] == '\n')
			commands[0][len-1] = 0;
		len = strlen(commands[1]);
		if(commands[1][len-1] == '\n')
			commands[1][len=1] = 0;
		len = strlen(commands[2]);
		if(commands[2][len-1] == '\n')
			commands[2][len-1] = 0;

		printf("index is %d \n", index);
		printf("commands[0] = %s commands[1] = %s commands[2] = %s \n", commands[0], commands[1], commands[2]);

		/* checks input for commands to do things */
		if( strcmp(commands[0], "submit") == 0 ){
			int check;
			if( check = queue_insert(q, commands[1]) < 0 )
				printf("queue full type showobs and when there is a spot open try again\n");
			else{
				//fork it and add to the queue
				jobs++;
				ptr = localtime(NULL);
				char *t = asctime(ptr);
				list[jobs-1].job_ids = jobs-1;
				list[jobs-1].name = commands[1];  
				list[jobs-1].start = t;
				list[jobs-1].status = "running";
				
				/* execvp it in redirect.h */
				redirect(index, commands, jobs-1, list);
				printf("job %d added to the queue\n", list[jobs-1].job_ids);
				
			}

			fflush(stdin);
		}

		if( strcmp(commands[0], "showjobs") == 0 ){
			if(jobs != 0){
				int i;
				printf("jobid\tcommands\tstatus\n");
				for(i=0;i<jobs-1;i++){
					printf("%d\t", list[i].job_ids);
					printf("%s\t", list[i].name);
					printf("%s\n", list[i].status);
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
