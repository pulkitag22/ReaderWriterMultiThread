#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "definations.h"

int main (void) {
	pthread_t tidReader[NUMBER_OF_READERS], tidWriter[NUMBER_OF_WRITERS];
	int i;	
	for (i=0; i<NUMBER_OF_READERS; i++){
		gIDOfReadThread[i] = i;
		if(pthread_create(&tidReader[i], NULL, readerMain, &gIDOfReadThread[i]) != 0 ){
			fprintf(stderr, "Unabe to create new thread.");
			exit(1);
		}
	}
	
	for (i=0; i<NUMBER_OF_WRITERS; i++){
		gIDOfWriteThread[i] = i;
		if(pthread_create(&tidWriter[i], NULL, writerMain, &gIDOfWriteThread[i]) != 0 ){
			fprintf(stderr, "Unabe to create new thread.");
			exit(1);
		}
	}
	
	for (i=0; i<NUMBER_OF_READERS; i++)
		pthread_join(tidReader[i], NULL);
	for (i=0; i<NUMBER_OF_WRITERS; i++)
		pthread_join(tidWriter[i], NULL);
	
	printf("Parent Quiting.");
	return 0;
}

void * readerMain (void * readerID){
	int * readerIDPtr = (int *)readerID;
	int readerID_loc = *readerIDPtr;
	
	for (int i=0; i<NUMBER_OF_READS; i++){
		pthread_mutex_lock (&gSharedMemoryLock);
			gNumberOfReadersOnline++;
			while (gReaderFlag != 0){
				pthread_cond_wait (&c_youCanRead, &gSharedMemoryLock);
			}	
			gNumberOfReadersOnline--;
			gReaderFlag++;
		pthread_mutex_unlock (&gSharedMemoryLock);

		fprintf (stdout, "Read Thread ID: %d || Value id Shared memory is %d\n", readerID_loc, gSharedResource);
		fprintf (stdout, "Currently %d Readers waiting...\n", gNumberOfReadersOnline);

		pthread_mutex_lock (&gSharedMemoryLock);
			if (gNumberOfReadersOnline == 0){
				gReaderFlag = -1;
				pthread_cond_signal (&c_youCanWrite);
			} else {
				gReaderFlag = 0;
				pthread_cond_broadcast(&c_youCanRead);
			}
		pthread_mutex_unlock(&gSharedMemoryLock);
	}
	pthread_exit(0);
}

void * writerMain (void * writerID) {
	int * writerIDPtr = writerID;
	int writerID_loc = *writerIDPtr;

	for (int i=0; i<NUMBER_OF_WRITES; i++){
		pthread_mutex_lock(&gSharedMemoryLock);
			while (gReaderFlag != -1) {
				pthread_cond_wait (&c_youCanWrite, &gSharedMemoryLock);
			}
			gReaderFlag = 1;		
		pthread_mutex_unlock(&gSharedMemoryLock);
		gSharedResource++;
		fprintf (stdout, "Writer Thread ID is %d || Old Value of the shared resourse is %d, Updated value is %d\n", writerID_loc,  gSharedResource-1, gSharedResource);

		pthread_mutex_lock (&gSharedMemoryLock);
			if (gNumberOfReadersOnline !=0){
				gReaderFlag = 0;
				pthread_cond_broadcast(&c_youCanRead);
			} else {
				gReaderFlag = -1;
				pthread_cond_signal(&c_youCanWrite);
			}
		pthread_mutex_unlock(&gSharedMemoryLock);
	}
	pthread_exit(0);
}
