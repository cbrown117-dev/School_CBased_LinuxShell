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

void printcommands(char **, int);

int main(int argc, char **argv){
	int numCores, index = 0, jobs = 0;

	if(argc < 2){  printf("need more arguents <program to run>\n");  exit(-1); }
	numCores = atoi(argv[1]);

	queue *q = queue_init(10);

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

		if( index > 1 ){ 
			int len = strlen(commands[0]);
			if(commands[0][len-1] == '\n')
				commands[0][len-1] = '\0';
			len = strlen(commands[1]);
			if(commands[1][len-1] == '\n')
				commands[1][len=1] = '\0';
			len = strlen(commands[2]);
			if(commands[2][len-1] == '\n')
				commands[2][len-1] = '\0';
		
//			printf("commands[0] = %s commands[1] = %s commands[2] = %s \n", commands[0], commands[1], commands[2]);
		}
		else{
			int len = strlen(commands[0]);
			if(commands[0][len-1] == '\n')
				commands[0][len-1] = 0;
		}

		/* checks input for commands to do things */
		if( strcmp(commands[0], "submit") == 0 ){
			int check;
			if( (check = queue_insert(q, commands[1], jobs, "running")) > numCores )
				q->status[(q->end) -1 % q->size] = "waiting";
			else{
				//fork it and add to the queue
				redirect(1,commands, jobs, q);
				printf("job %d added to the queue\n", jobs);
				jobs++;
				
			}

			fflush(stdin);
		}

		if( strcmp(commands[0], "showjobs") == 0 ){
				queue_display(q);
		}
			
		if( strcmp(commands[0], "deleteQ") == 0 ){
			queue_delete(q,  jobs);
		}	
	
		if( strcmp(commands[0], "submithistory") == 0 ){
			redirect(2, commands, jobs, q);
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
