/**
 * Esse é o processo consumidor que obtém a sequência de Collatz
 * do segmento de memória compartilhada.
 *
  * Fundamentos de Sistemas Operacionais, Nona Edição
 * Copyright John Wiley & Son - 2013.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	const char *name = "COLLATZ";
	const int SIZE = 4096;

	int shm_fd;
	void *ptr;
	int i;

	/* abre o segmento de memória compartilhada */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	/* agora mapeia o segmento de memória compartilhada no espaço de endereço do processo */
	ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	/* lê na região de memória compartilhada */
	printf("%s",(char *)ptr);

	/* remove o segmento de memória compartilhada */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}
