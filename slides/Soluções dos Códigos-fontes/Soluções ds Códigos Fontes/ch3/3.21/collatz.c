/**
 * Exibe a sequência de Collatz no processo filho.
 *
 * Solução do exercício 3.21
 *
 * Fundamentos de Sistemas Operacionais, Nona Edição
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define is_even(N) ( ((N % 2) == 0) ? 1 : 0)

int main(int argc, char *argv[])
{
pid_t pid;
int n;

	if (argc == 1) {
		fprintf(stderr,"Usage: ./a.out <starting value>\n");
		
		return -1;
	}

	n = atoi(argv[1]);

	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Unable to fork child\n");

		return -1;
	}
	else if (pid == 0) { /* processo filho */
		printf("%d, ",n);
		while (n != 1) {
			if (is_even(n))
				n = n / 2;
			else
				n = 3 * n + 1;
			printf("%d, ",n);
		}
	}
	else { /* processo pai */
		wait(NULL);
	}

	return 0;
}
