/**
 * Versão paralela do cálculo de Pi 
 * com o uso do OpenMP.
 *
 * Compilação:
 *	gcc -fopenmp main.c
 * 
 * Solução do exercício 4.23
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void worker(void);

#define NUMBER_OF_DARTS		50000000

/* número de ocorrências no círculo */
int circle_count = 0;

/*
 * Gera um número aleatório de precisão dupla
 */
double random_double() 
{
	return random() / ((double)RAND_MAX + 1);
}

int main (int argc, const char * argv[]) {
	int i;
	double estimated_pi;

	/* alimenta o gerador de números aleatórios */
	srandom((unsigned)time(NULL));
	
	#pragma omp parallel
	{
		worker();
	}
	
	
	/* estima Pi */
	estimated_pi = 4.0 * circle_count / (NUMBER_OF_DARTS * omp_get_num_procs());
	
	printf("Pi = %f\n",estimated_pi);
	
	return 0;
}

void worker(void)
{
	int i;
	int hit_count = 0;
	double x,y;

	for (i = 0; i < NUMBER_OF_DARTS; i++) {
		
		/* gera números aleatórios entre -1.0 e +1.0 (excluindo esse último)*/
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;
		
		if ( sqrt(x*x + y*y) < 1.0 )
			++hit_count;		
	}
	
	circle_count += hit_count;
	
	return;
}
