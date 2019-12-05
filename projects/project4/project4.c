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

#include "myinclude.h"

typedef struct{
	pid_t id;
	char *name;
}pid_process;

typedef struct{
	char names[100][100];
	int job_ids[100];
	char startTime[200];
	char endTime[200];
}hyLog;

void redirectRight(int, char**);

int main(int argc, char **argv){
	pid_t pid;
	pid_process array[10];
	
	int status, check_status = 0, index = 0;

	if(argc < 2){  printf("need more arguents <program to run>\n");  exit(-1); }

	printf("Enter command> ");
	char ch[150];
	fgets(ch,150,stdin);
	fprintf(build_hy,"%s ", ch);

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

		/* checks input for commands to do things */

		if( strcmp(ch, "submit\n") == 0 ){
			
			fflush(stdin);
		}

		else if( strcmp(ch, "showjobs\n") ==0 )
			
		else if( strcmp(ch, "submithistory\n") == 0 ){
			
		}	
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
