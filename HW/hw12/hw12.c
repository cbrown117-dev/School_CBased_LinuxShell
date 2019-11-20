#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct my_threads{
	pthread_t ptid;
	double sum;
	int N;
	int size;
	int tid;

}THREAD;

void *compute(void *arg){
	int myStart, myEnd, myN, i;

	THREAD *threads = (THREAD *)arg;
	//determine start and end of computation for the current thread
	myN = threads->N / threads->size;
	myStart = threads->tid * myN;
	myEnd = myStart + myN;
	if (threads->tid == (threads->size-1)) myEnd = threads->N;
	
	//compute partial sum
	double mysum = 0.0;
	for (i=myStart;i<myEnd;i++)
		mysum += (double)(i + 1);

	//grab the lock, update sum and release lock
	threads->sum += mysum;
	

	return(NULL);
}

int main(int argc, char **argv){
	long i;
	pthread_t *tid;

	if( argc != 3 ){
		printf("Usage: %s <# of elements> <# of threads>\n", argv[0]);
		exit(-1);
	}

	//set up struct
	
	int numElements = atoi(argv[1]);
	int numThreads = atoi(argv[2]);
	
	THREAD threads[numThreads];

	//create threads
	for (i = 0; i<numThreads;i++){
		threads[i].tid = i;
		threads[i].N = numElements;
		threads[i].size = numThreads;
		pthread_create(&threads[i].ptid, NULL, compute, (void *)&threads[i]);
	}

	double totalsum = 0.0;
	//wait for them to complete
	for(i=0;i<numThreads;i++){
		pthread_join(threads[i].ptid, NULL);
		totalsum += threads[i].sum;
	}

	printf("The total is %g, it should be equal to %g\n",
		totalsum, ((double)numElements*(numElements+1))/2);

	

	return 0;
}
