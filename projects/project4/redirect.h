#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#define MAX_LEN 1000
typedef struct{
	char *name;                                                                                                                                                                                                                                  int job_ids;                                                                                                                                                                                                                                 char *start;
	char *end;
	char *status;
}hyLog;

static void redirect(int argc, char **argv, int place, hyLog *hy){
	printf("called to redirect.h\n");
	pid_t pid;
	int fdout, status;

	if(argc < 2){
		printf("Usage: %s <command>[args]\n", argv[0]);
		exit(-1);
	}

	printf("argv[place] is %s\n", argv[place+1]);	
	
	pid = fork();
	if (pid == 0){ //this is the child
		printf("made it inside fork()\n");
		int pid_id = getpid();
		char buf[100];
		sprintf(buf, "%d.out", pid_id);

		/*
         	* open file to write standard output steam in append mode
         	* create a new file if the file does not exist
         	*/
		printf("before fdout()\n");
          	if( (fdout = open(buf, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1 ){
 	       		printf("Error opening file stdout.txt for output\n");
             		exit(-1);
		}
			
		/*replace standard output stream with the file stdout.txt */
		dup2(fdout, 1);

		char *commands[] = {argv[1], argv[2], NULL};
		printf("%s  %s  %s\n", commands[0], commands[1], commands[2]);
		printf("before execvp\n");
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
		printf("Wait for the child process to terminate\n");			
		
		wait(&status);
					
		if( WIFEXITED(status) ){ /*child process terminated normally */
			printf("Child process exited with status = %d\n", WEXITSTATUS(status));
			/*parent process still has the file handle to stdou.txt,
			 * now that the child process is done, let us write to 
			 * the file stdout.txt using the write system call
			 */

			close(fdout);
				
		}
		else { /*child process did not terminate normally */
			printf("Child process did not terminate normally\n");
			/*look at the man page for wait (man 2 wait) to determine
			 * how the child process was terminated
			 */
		}			
		
	} 
		
	else{ /*we have an error */
		perror("fork");
		exit(EXIT_FAILURE);   
	}
		
}
