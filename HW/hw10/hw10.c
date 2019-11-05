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

int main (int argc, char **argv){
	        pid_t pid;
		FILE *fp;
		time_t curtime, begin, end;
		struct tm *loc_time;
		char str[MAX_LEN];
		char *result;
		int status;
		int fdin, fdout;
		

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

		
		fp = fopen(argv[1], "r");

		while( !feof(fp) ){
                	time_t curtime, begin, end;
			result = fgets(str, MAX_LEN, fp);
			char *token = strtok(result," ");
			char cmd[MAX_LEN]; 
			
			strcpy(cmd, token);
			token = strtok(NULL, " ");

			char *overall[] = {cmd, token, NULL};
			time(&begin); //start timer

printf("%s %s \n", overall[0], overall[1]);

			pid = fork();
			if (pid == 0){ //is the child i
                		
				char buf[50];
				sprintf(buf, "%d.pid", pid);
                		/*
                 		* open file to write standard output steam in append mode
                 		* create a new file if the file does not exist
                 		*/
                		if( (fdout = open(buf, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1 ){
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
				time(&end);
			}

			else if (pid > 0){ //this is the parent process

				/*output from the parent process still goes to stdout : -) */
				printf("Wait for the child process to terminate\n");
				time(&curtime); //gets cutrent time
				loc_time = localtime(&curtime); //local time
				
				//end time and record difference
				wait(&status);
				time(&end);
				end = time(NULL);

				if( WIFEXITED(status) ){ /*child process terminated normally */
					printf("Child process exited with status = %d\n", WEXITSTATUS(status));
					/*parent process still has the file handle to stdou.txt,
					 * now that the child process is done, let us write to 
					 * the file stdout.txt using the write system call
					 */
					
					close(fdout);
					close(fdin);

					/*write to log time it took*/
					FILE *to = fopen("log.txt", "wx");
					printf("started at: %s took: %f \n", asctime(loc_time), difftime(end, begin));
					fprintf(to,"started at: %s took: %f \n", asctime(loc_time), difftime(end, begin));
					fclose(to);

					/*since we opened the file in append mode, the above text 
					 * will be added after the output from the child process
					 */
				}
				else { /*child process did not terminate normally */
					printf("Child process did not terminate normally\n");
					/*look at the man page for wait (man 2 wait) to determine
					 * how the child process was terminated
					 */
				}
				//process should be done, now to write to file				
				
			} 
			
			else{ /*we have an error */
				perror("fork");
				exit(EXIT_FAILURE);
			}
			
		}

return 0;
}
