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

int countArgc(char[10][100]);

int main(int argc, char **argv){
	pid_t pid;
	int status, check_status = 0;

	if(argc < 2){  printf("need more arguements (a file to read and write to)\n"); }

	FILE *build_hy = fopen(argv[1], "w");
	int index = 0;

	printf("blazersh> ");
	char ch[150];
	fgets(ch,150,stdin);
	fprintf(build_hy,"%s ", ch);

	while( strcmp(ch, "quit\n") != 0 ){
		/*breaks down input into an array of strings */        
		char commands[6][100];
		char *token = strtok(ch, " ");
	
		while(token != NULL){
			printf("token is %s and index is %d\n", token, index);
                	strcpy(commands[index], token); 
			token  = strtok(NULL," ");
			index++;
		}

		strcpy(commands[index],"\0");

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


		else{ /* if the program works then execvp will not run  */
			
			int i, pos = 0, left = 0, right = 0;
			
			for(i=0;i<index;i++){
				if( strcmp(commands[i], "<") == 0 )
					left = 1; pos = i;
				if( strcmp(commands[i], ">") == 0 )
					right = 1;
			}
	
			if( left == 1 || right == 1){
				printf("blazersh> I see the < in the command line\n");
				redirect(index, commands, pos);	
			}	

			else{
				
				pid = fork();
				if( pid == 0 ){
				
					execvp(commands[0], commands);
				
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

					/* going to put jobs and continue commands here 
					 * might need to make a usrsig1 to send continue signal
					 */
				       	if ( strcmp(commands[0], "jobs") == 0 && check_status == 0){
						printf("\nPID\tProcess\n");
						int pid_id = getpid();
						printf("%d\t%s", pid_id, commands[0]);
					}

                			waitpid(-1, &status, WUNTRACED);
					check_status = 1;

	                	if(WIFEXITED(status) && strcmp(commands[0], "jobs") == 0){
        	                	printf("blazersh> \n");
                		}
				if(WIFEXITED(status)){
					printf("blazersh> child exited normally\n");
					check_status = 0;
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

