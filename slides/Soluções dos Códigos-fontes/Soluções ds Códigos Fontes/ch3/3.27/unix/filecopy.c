/**
 * filecopy.c
 * 
 * Esse programa copia arquivos usando um pipe.
 *
 * Usage:
 *	filecopy <input file> <output file>
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
	int rv;
	pid_t pid;
	int c;
	char rb[2], wb[2];	/* bytes para leitura/gravação */
	int ffd[2];		/* descritor do arquivo */
	int pfd[2];		/* descritor de arquivo do pipe */

	/* abre o arquivo de entrada */
	ffd[READ_END] = open(argv[1], O_RDONLY);
	
	if (ffd[READ_END] < 0) {
		fprintf(stderr,"Unable to open %s\n",argv[1]);
		return 1;
	}
	
	/* abre o arquivo de saída */
	ffd[1] = open(argv[2], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if (ffd[1] < 0) {
		fprintf(stderr,"Unable to open %s\n",argv[2]);

		/* fecha o arquivo de entrada */
		close(ffd[0]);

		return 1;
	}

	/* configura o pipe */
     if (pipe(pfd) == -1) {
     	fprintf(stderr,"Pipe failed");

		/* fecha os arquivos abertos */
		close(ffd[0]);
		close(ffd[1]);

		return 1;
	}

	/* agora cria os processos */
	pid = fork();
	
	if (pid < 0) {
		fprintf(stderr, "Fork Failed");

		/* fecha os arquivos */
		close(ffd[0]);
		close(ffd[1]);

		return 1;
	}

	if (pid > 0) {	/* parent */
		/* fecha a extremidade do pipe da qual não precisamos */
		close(pfd[READ_END]);

		/* lê no arquivo de entrada e grava no pipe */
		while ( (c = read(ffd[0], rb, 1)) > 0 ) {
			write(pfd[WRITE_END],rb, c);
		}

		/* fecha a extremidade de leitura do arquivo de entrada e a extremidade de gravação do pipe */
		close(ffd[0]);
		close(pfd[WRITE_END]);

		wait(NULL);
	}
	else { /* child */ 
		/* fecha a extremidade do pipe da qual não precisamos */
		close(pfd[WRITE_END]);

		/* lê no pipe e grava no arquivo de saída */
		while ( (c = read(pfd[READ_END], rb, 1)) > 0) {
			write(ffd[1], rb, c);
		}

		/* fecha a extremidade de gravação do arquivo de entrada e a extremidade de leitura do pipe */
		close(ffd[1]);
		close(pfd[READ_END]);
	}

	return 0;
}
