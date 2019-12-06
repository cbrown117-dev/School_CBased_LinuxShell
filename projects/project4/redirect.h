#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <signal.h>

#include "queue.h"

#define MAX_LEN 1000
typedef struct{
	char *name;
	int job_ids;
	char *start;
	char *end;
	char *status;
}hyLog;

void printhy(hyLog hy[10]);

static void redirect(int check, char **argv, int place, queue *q){
	pid_t pid;
	int fdout, status;
	struct tm* loc_time;
	time_t curtime;
	curtime = time(NULL);
	
	hyLog hy[10];
	
	if(check == 2){
		printhy(hy);
	}else{
	pid = fork();
	if (pid == 0){ //this is the child
		int pid_id = getpid();
		char buf[100];
		sprintf(buf, "%d.out", pid_id);

		/*
         	* open file to write standard output steam in append mode
         	* create a new file if the file does not exist
         	*/
          	if( (fdout = open(buf, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1 ){
 	       		printf("Error opening file stdout.txt for output\n");
             		exit(-1);
		}
			
		dup2(fdout, 1);

		char *commands[] = {argv[1], argv[2], NULL};

		execvp(commands[0], commands);

		/* since stdout is written to stdout.txt and not the terminal,
		 * we should write to stderr in case exec fails. we use  
		 * that writes the error message to stderr
		 */
		perror("exec");
		exit(-1);
	}

	else if (pid > 0){ //this is the parent process
	/*output from the parent process still goes to stdout : -) */
		loc_time = localtime(&curtime);		
		hy[place].start = asctime(loc_time);	
                hy[place].name = q->buffer[q->end % q->size];
                hy[place].job_ids = q->jobID[q->end % q->size];
                hy[place].status = "success";
                curtime = time(NULL);
                loc_time = localtime(&curtime);	

		if( WIFEXITED(status) ){ /*child process terminated normally */
			hy[place].end = asctime(loc_time);
			queue_delete(q, place);
				
		}

	close(fdout);

	} 
		
	else{ /*we have an error */
		perror("fork");
		exit(EXIT_FAILURE);   
	}
	}		
}

void printhy(hyLog hy[10]){
	printf("jobid\tcommand\tstarttime\tendtime\t\tstatus\n");
	int i;
	for(i=0;i<10;i++){
		if( strcmp(hy[i].status, "success") == 0 ){
			printf("%d\t%s\t%s\t%s\t\t%s\n", 
					hy[i].job_ids, hy[i].name, hy[i].start, hy[i].end, hy[i].status);
		}
	}
}
