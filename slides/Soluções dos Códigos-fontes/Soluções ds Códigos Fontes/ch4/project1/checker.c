/**
 * Solução multithread para a verificação da validade de um Sudoku
 * Solução do projeto 1
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 	11
#define PUZZLE_SIZE 		9

void *column_worker(void *param); 	/* thread que verifica colunas */
void *row_worker(void *param); 		/* thread que verifica linhas */
void *subfield_worker(void *param); 	/* thread que verifica subcampos */

/* exemplo de quebra-cabeça */
int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1] = {
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,5,3,4,6,7,8,9,1,2},
			{-1,6,7,2,1,9,5,3,4,8},
			{-1,1,9,8,3,4,2,5,6,7},
			{-1,8,5,9,7,6,1,4,2,3},
			{-1,4,2,6,8,5,3,7,9,1},
			{-1,7,1,3,9,2,4,8,5,6},
			{-1,9,6,1,5,3,7,2,8,4},
			{-1,2,8,7,4,1,9,6,3,5},
			{-1,3,4,5,2,8,6,1,7,9}
		};

int status_map[NUMBER_OF_THREADS] = {0};

/* estrutura de dados para a passagem de dados para os threads */
typedef struct
{
	int thread_number;
	int x;
	int y;
} parameters;

int main(int argc, char *argv[])
{
	int i,j;
	int count = 0;
	int rv = 1;
	pthread_t workers[NUMBER_OF_THREADS];

	parameters *data = (parameters *) malloc(sizeof(parameters));
	data->thread_number = count;
	data->x = 1;
	data->y = 1;

	pthread_create(&workers[data->thread_number], 0, row_worker, data);

	count++;
	data = (parameters *) malloc(sizeof(parameters));	
	data->thread_number = count;
	data->x = 1;
	data->y = 1;
	pthread_create(&workers[data->thread_number], 0, column_worker, data);

	count++;

	/* cria os threads que verificarão cada subcampo */
	for (i = 1; i < PUZZLE_SIZE; i = i + (PUZZLE_SIZE/3)) {
		for (j = 1; j < PUZZLE_SIZE; j = j + (PUZZLE_SIZE/3)) {
			data = (parameters *) malloc(sizeof(parameters));
			data->thread_number = count;
			data->x = i;
			data->y = j;
			pthread_create(&workers[data->thread_number], 0, subfield_worker, data);
			++count;
		}
	}	

	for (i = 0; i < count; i++)
		pthread_join(workers[i], NULL);

	/* check the status map */
	for (i = 0; i < NUMBER_OF_THREADS; i++) {
		if (status_map[i] == 0)
			rv = 0;
	}

	if (rv == 1)
		printf("Sudoku puzzle is valid\n");
	else
		printf("Sudoku puzzle is invalid\n");
	

	return 0;
}

void *row_worker(void *params)
{
	int i,j, k, status;
	int map[PUZZLE_SIZE + 1] = {0};

	parameters* p = (parameters *)params;

	for (i = 1; i < PUZZLE_SIZE + 1; i++) {
		for (j = 1; j < PUZZLE_SIZE + 1; j++) {
			map[puzzle[i][j]] = 1;	
		}

		/* verifica-se todos os dígitos de 1 .. 9 estão aparecendo */
		status = 1;
		for (k = 1; k < PUZZLE_SIZE + 1; k++) {
			if (map[k] == 0) {
				status = 0;
				break;
			}
		}

		if (status == 0)
			break;
		else {
			/* reinicializa o mapa */
			for (i = 0; i < PUZZLE_SIZE + 1; i++)
				map[i] = 0;
		}
	}

	if (status)
		status_map[p->thread_number] = 1;

	pthread_exit(0);
}

void *column_worker(void *params)
{
	int i,j, k, status;
	int map[PUZZLE_SIZE + 1] = {0};

	parameters* p = (parameters *)params;

	for (i = 1; i < PUZZLE_SIZE + 1; i++) {
		for (j = 1; j < PUZZLE_SIZE + 1; j++) {
			map[puzzle[j][i]] = 1;	
		}

		/* verifica-se todos os dígitos de 1 .. 9 estão aparecendo */
		status = 1;
		for (k = 1; k < PUZZLE_SIZE + 1; k++) {
			if (map[k] == 0) {
				status = 0;
				break;
			}
		}

		if (status == 0)
			break;
		else {
			/* reinicializa o mapa */
			for (i = 0; i < PUZZLE_SIZE + 1; i++)
				map[i] = 0;
		}
	}

	if (status)
		status_map[p->thread_number] = 1;

	pthread_exit(0);
}

void *subfield_worker(void *params)
{
	int i,j, k, status;
	int map[PUZZLE_SIZE + 1] = {0};

	parameters* p = (parameters *)params;

	for (i = p->x; i < p->x + (PUZZLE_SIZE/3); i++) {
		for (j = p->y; j < p->y + (PUZZLE_SIZE/3); j++) {
			map[puzzle[j][i]] = 1;	
		}
	}

	/* verifica-se todos os dígitos de 1 .. 9 estão aparecendo */
	status = 1;
	for (k = 1; k < PUZZLE_SIZE + 1; k++) {
		if (map[k] == 0) {
			status = 0;
			break;
		}
	}

	if (status)
		status_map[p->thread_number] = 1;

	pthread_exit(0);
}
