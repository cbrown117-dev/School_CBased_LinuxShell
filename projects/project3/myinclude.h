#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

char* printcwd();
void list();
void change(char *);
void help();


//prints cwd
char* printcwd(){
	long size;
	char *buf;
	char *ptr;

	
	size = pathconf(".", _PC_PATH_MAX);


	if ((buf = (char *)malloc((size_t)size)) != NULL)
    		ptr = getcwd(buf, (size_t)size);

	return ptr;
}

//list all files in current directory
void list(){
          struct dirent *dirent;
	  DIR *parentDir;
	  char *ptr = printcwd();

	  parentDir = opendir (ptr);

	  if (parentDir == NULL) {
		  printf ("Error opening directory '%s'\n", ptr);
		  exit (-1);
	  }

	  while((dirent = readdir(parentDir)) != NULL){
		  if( strcmp((*dirent).d_name, ".") == 0 || strcmp((*dirent).d_name, "..") == 0 )
			  continue;
		  printf ("\t%s\n", (*dirent).d_name);
          }

	  closedir (parentDir);
}

//changes the pwd
void change(char *cd){
	int i, j = 0;
	char str[100];

	for(i=0;i<strlen(cd);i++){
		if(i > 2)
			str[j] = cd[i];		
	}

	//str = what directory they want
	chdir(str);
	printf("blazersh>%s\n", printcwd());
}

//prints help commands
void help(){
	printf("\ttype list to get all files and directories in current directory\n");
	printf("\ttype cd <directory> to change directories\n");
	printf("\ttype help for this display\n");
	printf("\ttype history to see what all you have typed in this console\n");
	printf("\ttype quit to stop\n");  
}

static void sig_usr(int signo){
	int pid = getpid();
	switch(signo){
		case SIGINT:
			printf("process with pid=%d is interrupted\n", pid);
			kill(pid, SIGINT);
			break;
		case SIGQUIT:
                        printf("recieved SIGQUIT signal %d\n killing parent", signo);
			int ppid = getppid();
			kill(ppid, SIGQUIT);
			break;  
		case SIGTSTP:
			printf("process with pid=%d is stopped\n", pid);
			/*int response = 0;
			char piece[10];
			sprintf(piece, "%d", pid);
			while(response == 0){
				char usr[20];
				printf("");
				fgets(usr, 21, stdin);
				char *token = strtok(usr, " ");
				char *token2 = strtok(NULL, " ");
				char *overall[] = {token, token2, NULL};
				if( strcmp(overall[0], "continue") == 0 ){
					printf("process %d started\n", pid);
					response = 1;
				}
				if( strcmp(overall[0], "jobs") == 0 ){
					printf("PID\t Process\n");
					printf("%d\t\n");
				}
			}*/
			break;
		default:
			printf("recieved signal %d\n", signo);
	}
}
