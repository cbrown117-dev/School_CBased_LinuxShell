 /*
 *chris Brown
 * sevrc
 * Project: 3
 */

// I copied existing code of mine that we made throughout this semester and used that
// the .h file has the code I took from
// and of course geeks for geeks .com
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include "myinclude.h"
#include "redirect.h"

typedef struct{
	pid_t id;
	char *name;
}pid_process;

void redirectRight(int, char**);

int main(int argc, char **argv){
	pid_t pid;
	pid_process array[10];
	
	int status, check_status = 0, index = 0;

	if(argc < 2){  printf("need more arguements (a file to read and write to)\n");  exit(-1); }

	FILE *build_hy = fopen(argv[1], "w");


	printf("blazersh> ");
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

		if( strcmp(ch, "hostname\n") == 0 ){
			printf("blazersh> %s\n", printcwd()); 
			fflush(stdin);
		}

		else if( strcmp(ch, "list\n") ==0 )
			list();

		else if ( strcmp(commands[0], "cd")== 0 )
			change(ch);
	
		else if( strcmp(ch, "history\n") == 0 ){
			fclose(build_hy);
			printf("blazersh>\n\thistory:\n");
			fflush(stdin);
			FILE *see_hy = fopen(argv[1],"r");
		
			while( !feof(see_hy) ){
				char hy[1000];
				fscanf(see_hy,"%s",hy);
				printf("\t\t%s\n", hy);
			}

				fclose(see_hy);
		}

		else if( strcmp(ch,"help\n")== 0 )
			help();

		else if( strcmp(commands[0], "jobs\n") == 0 ){
			int arrIndex;
			for(arrIndex = 0; arrIndex<check_status;arrIndex++){
				printf("PID\tProcess\n");
				printf("%d\t%s", array[arrIndex].id, array[arrIndex].name);
			}
		}

		else{ /* if the program works then execvp will not run  */
			array[check_status].id = getpid();
			array[check_status].name = pid_name;
			
			int i, left = 0, right = 0;
			
			for(i=0;i<index;i++){
				if( strcmp(commands[i], "<") == 0 ){
					printf("I see the < in the commands line\n");
					left = 1;
					redirect(index, commands, i+1);
				}
				if( strcmp(commands[i], ">") == 0 )
					right = 1;
			}

			if(right == 1 && left == 0){
				redirectRight(index, commands);
			}
	
			else if( right == 0 && left == 0 ){
				
				pid = fork();
				if( pid == 0 ){
					printf("made it to execvp in main\n");				
					execvp(cmd, commands);
				
					printf("blazersh> if you're seeing this the file may not exist or exec failed\n");
					printf("blazersh> make sure you have ./ infront of your file name\n");
					exit(-1);
				}
	
	        		else if (pid > 0){ //waits till child is done
					if(signal(SIGINT, sig_usr) == SIG_ERR){
						printf("can't catch SIGINT\n");
						exit(-1);
					}
					if(signal(SIGQUIT, sig_usr) == SIG_ERR){
						printf("can't catch SIGQUIT\n");
						exit(-1);
					}
	                                if(signal(SIGTSTP, sig_usr) == SIG_ERR){
						printf("can't catch SIGTSTP\n");
						exit(-1);
					}
					if(signal(SIGCONT,sig_usr) == SIG_ERR){
						printf("can't catch SIGCONT\n");
						exit(-1);
					}

					check_status++;
                			waitpid(-1, &status, WUNTRACED);

				if( WIFEXITED(status) ){
					printf("blazersh> child exited normally\n");
				}
                			else{
                        			printf("blazersh> child process did not terminate normally\n");
                			}
        			}
			}
		}

		char check[150];
		printf("blazersh> ");
		fflush(stdin);
		fflush(stdout);
		fgets(check, 150, stdin);
		strcpy(ch, check);
		fprintf(build_hy,"%s ",check);
		index = 0;
	}

	fclose(build_hy);

return 0;
}

void redirectRight(int index, char **commands){
	int fdout, status;
	pid_t pid;

	pid = fork();
	if( pid == 0 ){
		
		if( (fdout = open("stdout.txt", O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1 ){
			printf("Error opening file stdout.txt for output\n");
			exit(-1);
		}

		dup2(fdout, 1);
		printf("made it to execvp in redirectRight\n");
		execvp(commands[0], commands);
		printf("redirectRight failed error code: 1\n");
	}

	else if( pid > 0 ){
		printf("blazersh> Waiting on the child to complete\n");
		waitpid(-1, &status, WUNTRACED);

		if( WIFEXITED(status) ){
			printf("blazersh> exited normally\n");
			close(fdout);
		}
		else printf("blazersh> did not exit normally\n");
	}
}

