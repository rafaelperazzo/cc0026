/*
* @author Dustin Long 11/14/04
* This program creates a producer and consumer
* thread.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
HANDLE Mutex;
HANDLE SemEmpty, SemFull;
int insertPosition = 0, removePosition = 0, count =0;

// define the insert and remove methods
int insert_item(buffer_item);
int remove_item(buffer_item *);

// the code the producer thread runs
DWORD WINAPI Producer(LPVOID Param)
{
	buffer_item randomproduced;

	while (TRUE) {
		Sleep(2000);
		randomproduced = rand();
		if (insert_item(randomproduced)) {
			printf("could not insert item");
		}
		
	}

	return 0;
}

// the code the consumer thread runs
DWORD WINAPI Consumer(LPVOID Param)
{
	buffer_item random;

	while (TRUE) {
		Sleep(2000);
		if (remove_item(&random)) {
			printf("could not remove item");
		} else {
			
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int SleepTime, ProducerThreads, ConsumerThreads, i;
	DWORD ThreadId;
	HANDLE ConsumerThreadHandles [100], ProducerThreadHandles [100], CreatedThread;
	Mutex = CreateMutex(NULL, FALSE, NULL);
	SemFull = CreateSemaphore(NULL, 5, 5, NULL);
	SemEmpty = CreateSemaphore(NULL, 0, 5, NULL);

	//check for correct number of parameters
	if (argc != 4) {
		printf("must pass three positive integer parameters");
		return -1;
	}

	SleepTime = atoi(argv[1]);
	ProducerThreads = atoi(argv[2]);
	ConsumerThreads = atoi(argv[3]);

	// check for valid parameters
	if (SleepTime < 0 || ProducerThreads < 0 || ConsumerThreads < 0) {
		printf("must pass three positive integer parameters");
		return -1;
	}

	printf("\n");
	
	// create the producer threads and insert into array
	for (i = 0; i < ProducerThreads; i++) {
		CreatedThread = CreateThread(NULL, 0, Producer, NULL, 0, &ThreadId);
		ProducerThreadHandles[i] = CreatedThread;
	}

	// create the consumer threads and insert into array
	for (i = 0; i < ConsumerThreads; i++) {
		CreatedThread = CreateThread(NULL, 0, Consumer, NULL, 0, &ThreadId);
		ConsumerThreadHandles[i] = CreatedThread;
	}
	
	// sleep and allow the program to run
	Sleep(SleepTime);
	
	// join on threads
	WaitForMultipleObjects(ProducerThreads, ProducerThreadHandles, TRUE, 0);
	WaitForMultipleObjects(ConsumerThreads, ConsumerThreadHandles, TRUE, 0);
	CloseHandle(ProducerThreadHandles);
	CloseHandle(ConsumerThreadHandles);
	return 0;
}

int insert_item(buffer_item item) {
	WaitForSingleObject(SemFull, INFINITE);
	WaitForSingleObject(Mutex, INFINITE);

	//insert the item
	++count;
	printf("producer produced %d count = %d\n", item, count);
	buffer[insertPosition] = item;
	++insertPosition;
	if (insertPosition >= 5) {
		insertPosition = 0;
	} else if (insertPosition < 0 || count > 5) {
		// print out error and return -1
		printf("error removing item!!!");
		return -1;
	}

	//release the mutex and semempty to allow remove to run
	ReleaseMutex(Mutex);
	ReleaseSemaphore(SemEmpty, 1, NULL);

	return 0;
}

int remove_item(buffer_item *item) {
	WaitForSingleObject(SemEmpty, INFINITE);
	WaitForSingleObject(Mutex, INFINITE);

	// remove the item
	--count;
	item[0] = buffer[removePosition];
	printf("                           consumer consumed %d count = %d\n", item[0], count);
	++removePosition;
	if (removePosition >= 5) {
		removePosition = 0;
	} else if (removePosition < 0 || count < 0) {
		// print out error and return -1
		printf("error removing item!!!");
		return -1;
	}

	// release the mutex and semfull to allow insert to run
	ReleaseMutex(Mutex);
	ReleaseSemaphore(SemFull, 1, NULL);

	return 0;
}
