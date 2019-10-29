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
		time_t curtime, begin, end;
		struct tm *loc_time;
		char str[MAX_LEN];
		char *result;
		int status;

		if(argc < 2){
			printf("Usage: %s <command>[args]\n", argv[0]);
			exit(-1);
		}

		fp = fopen(argv[1],"r");
		fp2 = fopen(argv[2], "w");
		
		int ch = getc(fp);
	
		while( ch != EOF){
			result = fgets(str, MAX_LEN, fp);
			char *token = strtok(result," ");
			char cmd[MAX_LEN]; 
			
			strcpy(cmd, token);
			token = strtok(NULL, " ");

			char *overall[] = {cmd, token, NULL};
			time(&begin); //start timer

			pid = fork();
			if (pid == 0){ //is the child 
				execvp(overall[0], &overall);
				time(&end);
				printf("if you see this statement then exec failed ; -(\n");
				exit(-1);
			}

			else if (pid > 0){ //this is the parent process
				 if(feof(fp)){ break;} 

				printf("Wait for the child process to terminate\n");
				time(&curtime); //gets cutrent time
				loc_time = localtime(&curtime); //local time
				
				//end time and record difference
				wait(&status);
				end = time(NULL);

				//process should be done, now to write to file				
				fprintf(fp2," %s %s time: %s  it took %f seconds to complete \n",overall[0], overall[1], asctime(loc_time), difftime(end, begin));
			}
			
		}
		
		fclose(fp);
		fclose(fp2);

return 0;
}
