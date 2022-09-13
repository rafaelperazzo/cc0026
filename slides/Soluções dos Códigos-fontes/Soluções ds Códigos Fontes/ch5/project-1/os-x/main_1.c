#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "ta.h"

pthread_t ta;
pthread_t students[NUM_OF_STUDENTS];

/**
 * Initialize all relevant data structures and
 * synchronization objects.
 */
void init()
{
int i;

	if ( pthread_mutex_init(&mutex_lock, NULL) != 0)
		printf("%s\n",strerror(errno));

	/** OS X code */
	
	/** Remove semaphores if they currently exist */
	if (sem_unlink("STUDENTS") == -1)
		printf("%s\n",strerror(errno));
	
	if (sem_unlink("TA") == -1)
		printf("%s\n",strerror(errno));
	
	/** Initialize the semaphores */
	if ( (students_sem = sem_open("STUDENTS", O_CREAT, 0666, 0)) == SEM_FAILED)
		printf("%s\n",strerror(errno));
	
	if ( (ta_sem = sem_open("TA", O_CREAT, 0666, 0)) == SEM_FAILED)
		printf("%s\n",strerror(errno));

	waiting_students = 0;

	for (i = 0; i < NUM_OF_STUDENTS; i++)
		student_id[i] = i;
}

void create_students()
{
int i;

	for (i = 0; i < NUM_OF_STUDENTS; i++) {
		pthread_create(&students[i], 0, student_loop, (void *)&student_id[i]);
	}
}

void create_ta()
{
	pthread_create(&ta, 0, ta_loop, 0);
}

int main(void)
{
int i;

	init();

	create_ta();

	create_students();

	for (i = 0; i < NUM_OF_STUDENTS; i++)
		pthread_join(students[i], NULL);

	/* when all students have finished, we will cancel the TA thread */	
	if (pthread_cancel(ta) != 0)
		printf("%s\n",strerror(errno));

	return 0;
}

