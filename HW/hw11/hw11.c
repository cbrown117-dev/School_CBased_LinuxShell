#include<stdio.h>
#include<stdlib.h>

int main (int argc, char **argv){
	FILE *fp;
	char str[1024];
	char line[1024];

	printf("command: ");
	fgets(str, 1024, stdin);
	printf("\n");

	while( strcmp(str, "quit\n") != 0 ){
		if( (fp = popen(str, "r")) == NULL ){
			perror("popen");
			exit(EXIT_FAILURE);
		}

		while( fgets(line, 1024, fp) != NULL){
			if( fputs(line, stdout) == EOF ){
				printf("Error writing to pipe\n");
				exit(EXIT_FAILURE);
			}
		}

		/* wait for child to process to terminate */
		if ( pclose(fp) == -1 ){
			perror("pclose");
			exit(EXIT_FAILURE);
		}
		
	      	printf("command: ");
		fflush(stdin);
		fgets(str, 1024, stdin);
		printf("\n");

	}


return 0;

}
