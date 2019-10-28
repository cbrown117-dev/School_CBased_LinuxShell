 /*
 *chris Brown
 * sevrc
 * Project: 1
 */

// I put all my exisiting code into a .h file and called that

#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void printcwd();

int main(int argc, char **argv){
	char history[100][100];
	int i = 1;

	printf("blazersh> ");
	char ch[150];
	gets(ch);

	//strcpy(history[0], "history:");
	

	while( strcmp(ch, "quit") != 0 ){
		//strcat last command into full history 2d array
		//strcpy(history[i], ch);
		

		if( strcmp(ch, "hostname") == 0 )
			printcwd();
		if( strcmp(ch, "list") ==0 ){
			printf("will call myinclude.h traversal(), then print out files\n");
		}
		if ( strcmp(ch, "cd")== 0 ) //will have to fix this
			printf("cd into what?\n");

		if( strcmp(ch, "history") == 0 ){
			int j = 0;
			for(j=0;j<i;j++){
				printf("%s\n", history[j]);
			}
		}

		char check[150];
		printf("blazersh> ");
		gets(check);
		strcpy(ch, check);
		i++;
	}


return 0;
}

void printcwd(){
	long size;
	char *buf;
	char *ptr;


	size = pathconf(".", _PC_PATH_MAX);


	if ((buf = (char *)malloc((size_t)size)) != NULL)
    		ptr = getcwd(buf, (size_t)size);

	printf("%s\n", ptr);
}
