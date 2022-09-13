/*
 * Solução do Windows para o exercício 4.26
 *
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <stdio.h>
#include <windows.h>


/** só permitiremos até 256 números de fibonacci */
#define MAX_SIZE 256

int fibs[MAX_SIZE];


/* o thread é executado nessa função separada */
DWORD WINAPI Summation(PVOID Param)
{
    DWORD upper = *(DWORD *)Param;
	int i;


	if (upper== 0)
		return 0;
	else if (upper == 1)
		fibs[0] = 0;
	else if (upper== 2) {
		fibs[0] = 0;
		fibs[1] = 1;
	}
	else { // sequência > 2
		fibs[0] = 0;
		fibs[1] = 1;

		for (i = 2; i < upper; i++)
			fibs[i] = fibs[i-1] + fibs[i-2];
	}

	return 0;
}


int main(int argc, char *argv[])
{
	DWORD ThreadId;
	HANDLE ThreadHandle;
	int Param;

	// faz alguma verificação de erros básica
	if (argc != 2) {
		fprintf(stderr,"An integer parameter is required\n");
		return -1;
	}

	Param = atoi(argv[1]);

	if ( (Param < 0) || (Param > 256) ) {
		fprintf(stderr, "an integer >= 0 and < 256 is required \n");
		return -1;
	}

	// cria o thread
	ThreadHandle = CreateThread(NULL, 0, Summation, &Param, 0, &ThreadId);

	if (ThreadHandle != NULL) {
		WaitForSingleObject(ThreadHandle, INFINITE);
		CloseHandle(ThreadHandle);

                /** agora exibe os números de Fibonacci */
                for (int i = 0; i < Param; i++)
                    printf("%d\n", fibs[i]);
	}
}
