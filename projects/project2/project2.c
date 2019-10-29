 /*
 *chris Brown
 * sevrc
 * Project: 2
 */

// I copied existing code of mine that we made throughout this semester and used that
// the .h file has the code I took from

#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

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
		
		if( strcmp(ch, "hostname\n") == 0 )
			printf("blazersh> %s\n", printcwd());

		if( strcmp(ch, "list\n") ==0 )
			listing();

		if ( strcmp(token, "cd")== 0 )
			change(ch);
	
		if( strcmp(ch, "history\n") == 0 ){
			fclose(build_hy);
			printf("blazersh>history:\n");
			FILE *see_hy = fopen(argv[1],"r");
		
			while( !feof(see_hy) ){
				char hy[1000];
				fscanf(see_hy,"%s",hy);
				printf("\t%s\n", hy);
			}

				fclose(see_hy);
		}

		if( strcmp(ch,"help\n")== 0 )
			help();
/*
		else{
                	char cmd[100];

                	strcpy(cmd, token);
                	token = strtok(NULL, " ");
			printf("%s %s \n", cmd, token);
                	char *overall[] = {cmd, token, NULL};
                	printf("%s %s \n", cmd, token);
			
			pid = fork();
			if( pid == 0 ){
				execvp(overall[0], overall);
				printf("blazersh> if you're seeing this the file may not exist or exec failed\n");
			}
		}
*/
		char check[150];
		printf("blazersh> ");
		fflush(stdin);
		fgets(check, 150, stdin);
		strcpy(ch, check);
		fprintf(build_hy,"%s ",check);
		i++;
	}

/*
	if (pid > 0){ //waits till child is done
		wait(&status);
		if(WIFEXITED(status)){
			printf("blazersh> child process exited with status = %d\n", WEXITSTATUS(status));
		}
		else{
			printf("blazersh> child process did not terminate normally\n");
		}
	}
*/
	fclose(build_hy);

return 0;
}

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
void listing(){
          struct dirent *dirent;
	  DIR *parentDir;
	  char *ptr = printcwd();

	  parentDir = opendir (ptr);

	  if (parentDir == NULL) {
		  printf ("Error opening directory '%s'\n", ptr);
		  exit (-1);
	  }

	  while((dirent = readdir(parentDir)) != NULL){
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
