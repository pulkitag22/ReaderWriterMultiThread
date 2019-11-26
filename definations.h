#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMBER_OF_READERS 5
#define NUMBER_OF_WRITERS 5
#define NUMBER_OF_READS 5
#define NUMBER_OF_WRITES 5

int gIDOfReadThread[NUMBER_OF_READS];	//To avoid wrong i value to be sent. Refer to Quiz 1,2,3 from the session.
int gIDOfWriteThread[NUMBER_OF_WRITERS];	//To avoid wrong i value to be sent. Refer to Quiz 1,2,3 from the session.

int gSharedResource = 0;
int gNumberOfReadersOnline = 0;
int gReaderFlag = 0;

pthread_mutex_t gSharedMemoryLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_youCanWrite = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_youCanRead = PTHREAD_COND_INITIALIZER;

void * readerMain (void * readerID);
void * writerMain (void * writerID);
