/**
 * Figure 3.32
 *
  * Para usar com o script python:
 *
 * (1) Compile esse programa:
 *          gcc loop-fork.c
 * (2) Envie a sa�da do programa para o script python:
 *          ./a.out | set.py
 * que exibir� o n�mero de ids de processo exclusivas.
 */

#include <stdio.h>

int main()
{
	int i;

	for (i = 0; i < 4; i++) {
		fork();
		printf("%d\n",getpid());
	}
	
	return 0;
}
