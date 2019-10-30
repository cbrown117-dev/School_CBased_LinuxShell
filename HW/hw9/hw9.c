#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static void sig_usr(int);
static void sig_int(int);

int main(int argc, char **argv) {
	    pid_t pid;
	    int status;
	
 
	    if (argc < 2) {
	            printf("Usage: %s <command> [args]\n", argv[0]);
	            exit(-1);
	    }

	    pid = fork();
	    if (pid == 0) { /* this is child process */
	    	execvp(argv[1], &argv[1]);
	        printf("If you see this statement then execl failed ;-(\n");
	    	exit(-1);

	    } else if (pid > 0) { /* this is the parent process */
		      printf("Wait for the child process to terminate\n");
		      if(signal(SIGINT, sig_usr) == SIG_ERR){
				printf("can't catch SIGINT\n");
		      		exit(-1);
		      }
		      if(signal(SIGQUIT, sig_usr) == SIG_ERR){
		      		printf("can't catch SIGINT\n");
				exit(-1);
		      }
		      if(signal(SIGTSTP,sig_usr)==SIG_ERR){
		      		printf("can't catch SIGTSTP\n");
				exit(-1);
		      }
		      wait(&status); /* wait for the child process to terminate */
		      if (WIFEXITED(status)) { /* child process terminated normally */
			      printf("Child process exited with status = %d\n", WEXITSTATUS(status));
			      } else { /* child process did not terminate normally */
				        printf("Child process did not terminate normally!\n");
				/* look at the man page for wait (man 2 wait) to determine
				   how the child process was terminated */
				}
	      } else { /* we have an error */
			perror("fork"); /* use perror to print the system error message */
			exit(EXIT_FAILURE);
	      }

  	    printf("[%ld]: Exiting program .....\n", (long)getpid());
  
	return 0;
}

static void sig_usr(int signo){
	int pid = getpid();
	switch(signo){
		case SIGINT:
			printf("recieved SIGINT signal %d\n", signo);
			kill(pid, SIGINT);
			break;
		case SIGQUIT:
		        printf("recieved SIGQUIT signal %d\n", signo);
			int ppid = getppid();
			kill(ppid,SIGQUIT);
		        break;	
                case SIGTSTP:
                        printf("recieved SIGTSTP signal %d\n", signo);
			printf("will pause\n ");
			pause();
                        break;
		default:
			printf("recieved signal %d\n", signo);			
	}

}

static void sig_int(int signo) {
	   ssize_t n;
	   char buf[2];

	   signal(signo, SIG_IGN); /* ignore signal first */
	   printf("Do you really want to do this: [Y/N]? ");
	   fflush(stdout);
	   n = read(STDIN_FILENO, buf, 2);
	   if ( buf[0] == 'Y' ) {
	           raise(SIGTERM); // or kill(0, SIGTERM); // or exit (-1); 
	   } else {
	          printf("Ignoring signal, be careful next time!\n");
	          fflush(stdout);
	    }

	 signal(signo, sig_int); /* reinstall the signal handler */
}
