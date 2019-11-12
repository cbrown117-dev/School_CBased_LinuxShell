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
		time_t curtime1,curtime2;
		struct tm *loc_time, *loc_time2;
		char str[MAX_LEN];
		char start[150]; char end[150];
		int status;

		if(argc < 2){
			printf("Usage: %s <command>[args]\n", argv[0]);
			exit(-1);
		}

		fp = fopen(argv[0],"r");
		fp2 = fopen(argv[2], "w");
		
		
	
		while( fgets(str, MAX_LEN, fp) != NULL){
		 	fgets(str, MAX_LEN, fp);
			char *token = strtok(str," ");
			char cmd[MAX_LEN]; 
			
			strcpy(cmd, token);
			token = strtok(NULL, " ");

			char *overall[] = {cmd, token, NULL};
			printf("%s %s \n", overall[0], overall[1]);
			curtime1 = time(NULL);
			loc_time = localtime(&curtime1);
			strcpy(start, asctime(loc_time));

			pid = fork();
			if (pid == 0){ //is the child 
				execvp(overall[0], overall);
				printf("if you see this statement then exec failed ; -(\n");
				exit(-1);
			}

			else if (pid > 0){ //this is the parent process

				printf("Wait for the child process to terminate\n");
				
				//end time and record difference
				wait(&status);
				
				curtime2 = time(NULL);
				loc_time2 = localtime(&curtime2);
				strcpy(end, asctime(loc_time2)); 
				
				//process should be done, now to write to file				
				fprintf(fp2," %s %s time started %s - ended:%s \n",overall[0], overall[1], start, end);
			}
			
		}
		
		fclose(fp);
		fclose(fp2);

return 0;
}
