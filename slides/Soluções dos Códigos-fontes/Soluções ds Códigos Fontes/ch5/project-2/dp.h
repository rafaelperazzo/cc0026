/**
 * Header file for dining philosophers
 */

#include <pthread.h>

// the number of philosophers
#define NUMBER 		5

// the maximum time (in seconds) to sleep
#define MAX_SLEEP_TIME	5

// different philosopher states
//#define THINKING		0
//#define HUNGRY			1
//#define EATING			2

// the state of each philosopher (THINKING, HUNGRY, EATING)
//int state[NUMBER];
enum {THINKING, HUNGRY, EATING} state[NUMBER];

// the thread id of each philosopher (0 .. NUMBER - 1)
int thread_id[NUMBER];

// condition variables and associated mutex lock
pthread_cond_t		cond_vars[NUMBER];
pthread_mutex_t 	mutex_lock;

void *philosopher(void *param);
