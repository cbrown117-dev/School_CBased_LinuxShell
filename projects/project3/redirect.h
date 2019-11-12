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

static void redirect(int argc, char **argv, int place){
	        printf("blazersh> called to redirect.h\n");
		pid_t pid;
		time_t curtime, curtime2;
		struct tm *loc_time; struct tm *loc_time2;
		
		char *start; char *end; char* command; char *command2;
		int fdin, fdout, err, status;
		FILE *fp; FILE *to = fopen("log.txt", "w");

		if(argc < 2){
			printf("Usage: %s <command>[args]\n", argv[0]);
			exit(-1);
		}

		/*
		 * open file to read standard input stream,
		 * make sure the file stdin.txt exists, even if it is empty
		 */
		if( (fdin = open("stdin.txt", O_RDONLY)) == -1 ){\
			printf("Error opening file stdin.txt for input\n");
			exit(-1);
		}

		
		fp = fopen(argv[place], "r");
		
		if(fp == NULL)
			printf("there might not be a file\n");

		pid = fork();
		if (pid == 0){ //is the child
			while( !feof(fp) ){
				char str[MAX_LEN];		
				char *result = fgets(str, MAX_LEN, fp);
				char *token = strtok(result," ");
				char cmd[MAX_LEN];
				strcpy(cmd, token);
				token = strtok(NULL, " ");
				char *overall[] = {cmd, token, NULL};
				
				strcpy(command, cmd);
				strcpy(command2, token);

				int pid_id = getpid();
			
				/*
               			* open file to write standard output steam in append mode
               			* create a new file if the file does not exist
               			*/
                		if( (fdout = open("stdout.txt", O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1 ){
       	                		printf("Error opening file stdout.txt for output\n");
               	        		exit(-1);
				}
				
			
				/*replace standard input stream with the file stdin.txt */
				dup2(fdin, 0);

				/*replace standard output stream with the file stdout.txt */
				dup2(fdout, 1);

				execvp(overall[0], overall);

				/* since stdout is written to stdout.txt and not the terminal,
				 * we should write to stderr in case exec fails. we use perror 
				 * that writes the error message to stderr
				 */
				perror("exec");
			}
		}

		else if (pid > 0){ //this is the parent process
			/*output from the parent process still goes to stdout : -) */
			printf("Wait for the child process to terminate\n");
                        
		 	//time handle
			curtime = time(NULL);
			loc_time = localtime(&curtime);
			printf("first time %s\n", asctime(loc_time));
			strcpy(start, asctime(loc_time));				
			
			wait(&status);
						
			if( WIFEXITED(status) ){ /*child process terminated normally */
				printf("Child process exited with status = %d\n", WEXITSTATUS(status));
				/*parent process still has the file handle to stdou.txt,
				 * now that the child process is done, let us write to 
				 * the file stdout.txt using the write system call
				 */

				/*write to log time it took*/
				fprintf(to,"%s %s %s %s\n", command, command2, start,end);
				
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
			
	fclose(to);
}
