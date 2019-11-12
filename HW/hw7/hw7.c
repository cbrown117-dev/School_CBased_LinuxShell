#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define MAX_LEN 1000

int main (int argc, char **argv){
	        pid_t pid;
		FILE *fp, *fp2;
		time_t t1, t2;
		char str[MAX_LEN];
		char start[150]; char end[150];
		int status;
		int index = 0;

		if(argc < 2){
			printf("Usage: %s <command>[args]\n", argv[0]);
			exit(-1);
		}

		fp = fopen(argv[1],"r");
		fp2 = fopen(argv[2], "w");		
	
		while( fgets(str, MAX_LEN, fp) != NULL){
                	char *commands[10];
                	char cmd[50];
                	char *token = strtok(str, " ");

                	strcpy(cmd, token);

              	  	while(token != NULL){
                       	 	commands[index] = token;
                        	token  = strtok(NULL," ");
                        	index++;
                	}

			commands[index] = NULL;
						
			time(&t1);
			pid = fork();
			if (pid == 0){ //is the child 
				execvp(cmd, commands);
				printf("if you see this statement then exec failed ; -(\n");
				exit(-1);
			}

			else if (pid > 0){ //this is the parent process

				printf("Wait for the child process to terminate\n");
				
				//end time and record difference
				wait(&status);
								
				//process should be done, now to write to file				
				fprintf(fp2," child started at %s \n",ctime(&t1) );
			}
			
		}
		
		fclose(fp);
		fclose(fp2);

return 0;
}
