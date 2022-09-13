/**
 * Vers�o paralela do c�lculo de Pi 
 *
 * Solu��o do exerc�cio 4.22
 *
 * Compila��o:
 *	gcc -lpthread parallel.c
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void *worker(void *param);

#define NUMBER_OF_DARTS		50000000
#define NUMBER_OF_THREADS	2

/* n�mero de ocorr�ncias no c�rculo */
int circle_count = 0;

/*
 * Gera um n�mero aleat�rio de precis�o dupla
 */
double random_double() 
{
	return random() / ((double)RAND_MAX + 1);
}

int main (int argc, const char * argv[]) {
	int darts_per_thread = NUMBER_OF_DARTS/ NUMBER_OF_THREADS;
	int i;
	
	double estimated_pi;
	
	pthread_t workers[NUMBER_OF_THREADS];

	/* alimenta o gerador de n�meros aleat�rios */
	srandom((unsigned)time(NULL));

	for (i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&workers[i], 0, worker, &darts_per_thread);
	
	for (i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(workers[i],NULL);
	
	/* estima Pi */
	estimated_pi = 4.0 * circle_count / NUMBER_OF_DARTS;

	printf("Pi = %f\n",estimated_pi);
	
	return 0;
}

void *worker(void *param)
{
	int number_of_darts;
	number_of_darts = *((int *)param);
	int i;
	int hit_count = 0;
	double x,y;
	
	for (i = 0; i < number_of_darts; i++) {
		
		/* gera n�meros aleat�rios entre -1.0 e +1.0 (excluindo esse �ltimo)*/
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;
		
		if ( sqrt(x*x + y*y) < 1.0 )
			++hit_count;		
	}
	
	circle_count += hit_count;
	
	pthread_exit(0);
}

