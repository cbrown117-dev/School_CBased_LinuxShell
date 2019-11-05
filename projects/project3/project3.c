 /*
 *chris Brown
 * sevrc
 * Project: 3
 */

// I copied existing code of mine that we made throughout this semester and used that
// the .h file has the code I took from

#include <stdlib.h>
#include <stdio.h>

#include "myinclude.h"

char* printcwd();
void listing();
void change(char *);
void help();

int main(int argc, char **argv){
	pid_t pid;
	int status;

	if(argc < 2){  printf("need more arguements (a file to read and write to)\n"); }

	FILE *build_hy = fopen(argv[1], "w");
	int i = 1;

	printf("blazersh> ");
	char ch[150];
	fgets(ch,150,stdin);
	fprintf(build_hy,"%s ", ch);

		
	while( strcmp(ch, "quit\n") != 0 ){
               	char *token = strtok(ch," ");
		
		if( strcmp(ch, "hostname\n") == 0 ){
			printf("blazersh> %s\n", printcwd()); 
			fflush(stdin);
		}

		else if( strcmp(ch, "list\n") ==0 )
			listing();

		else if ( strcmp(token, "cd")== 0 )
			change(ch);
	
		else if( strcmp(ch, "history\n") == 0 ){
			fclose(build_hy);
			printf("blazersh>history:\n");
			fflush(stdin);
			FILE *see_hy = fopen(argv[1],"r");
		
			while( !feof(see_hy) ){
				char hy[1000];
				fscanf(see_hy,"%s",hy);
				printf("\t%s\n", hy);
			}

				fclose(see_hy);
		}

		else if( strcmp(ch,"help\n")== 0 )
			help();

		else{
                	char cmd[100];

                	strcpy(cmd, token);
                	token = strtok(NULL, " ");
                	char *overall[] = {cmd, token, NULL};
			
			pid = fork();
			if( pid == 0 ){
				execvp(overall[0], overall);
				printf("blazersh> if you're seeing this the file may not exist or exec failed\n");
				printf("blazersh> make sure you have ./ infront of your file name\n");
				exit(-1);
			}
        		else if (pid > 0){ //waits till child is done
                	wait(&status);
                	if(WIFEXITED(status)){
                        	printf("blazersh> child process exited with status = %d\n", WEXITSTATUS(status));
                	}
                		else{
                        		printf("blazersh> child process did not terminate normally\n");
                		}
        }
		}

		char check[150];
		printf("blazersh> ");
		fflush(stdin);
		fgets(check, 150, stdin);
		strcpy(ch, check);
		fprintf(build_hy,"%s ",check);
		i++;
	}

	fclose(build_hy);

return 0;
}

