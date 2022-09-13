/*
 * Solu��o do Windows para o exerc�cio 4.24
 *
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <stdio.h>
#include <windows.h>


/** s� permitiremos at� 256 n�meros primos */
#define MAX_SIZE 256

int primes[MAX_SIZE];


/* o thread � executado nessa fun��o separada */
DWORD WINAPI Summation(PVOID Param)
{
    DWORD upper = *(DWORD *)Param;

    int i, j;

	primes[1] = 0;
	for (i = 2; i <= upper; i++)
		primes[i] = 1;

	for (i = 2; i <= upper/2; i++)
		for (j = 2; j <= upper/i; j++)
			primes[i*j] = 0;
	return 0;
}


int main(int argc, char *argv[])
{
	DWORD ThreadId;
	HANDLE ThreadHandle;
	int Param;

	/* faz alguma verifica��o de erros b�sica */
	if (argc != 2) {
		fprintf(stderr,"An integer parameter is required\n");
		return -1;
	}

	Param = atoi(argv[1]);

	if (Param < 2) {
		fprintf(stderr, "an integer >= 2 is required \n");
		return -1;
	}

	/* cria o thread */
	ThreadHandle = CreateThread(NULL, 0, Summation, &Param, 0, &ThreadId);

	if (ThreadHandle != NULL) {
		WaitForSingleObject(ThreadHandle, INFINITE);
		CloseHandle(ThreadHandle);

                /** agora exibe os n�meros primos */
                for (int i = 1; i <= Param; i++)
                if (primes[i] > 0)
                    printf("%d\n", i);
	}
}
