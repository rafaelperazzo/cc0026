/**
 * Header file for dining philosophers
 */

#include <pthread.h>
#include <semaphore.h>

/* the maximum time (in seconds) to sleep */
#define MAX_SLEEP_TIME	5

/* number of maximum waiting students */
#define MAX_WAITING_STUDENTS	3

/* number of potential students */
#define NUM_OF_STUDENTS		5

/* number of available seats */
#define NUM_OF_SEATS	3

/* semaphores and mutex lock */
pthread_mutex_t 	mutex_lock;

/* OS X semaphore declarations */
sem_t			*students_sem;
sem_t			*ta_sem;

/* the number of waiting students */
int waiting_students;

/* student being served */
int student_number;

/* the numeric id of each student */
int student_id[NUM_OF_STUDENTS];

/* student function prototype */
void *student_loop(void *param);

/* ta function prototype */
void *ta_loop(void *param);

