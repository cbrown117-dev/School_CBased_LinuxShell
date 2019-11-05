#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

char* printcwd();
void listing();
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
