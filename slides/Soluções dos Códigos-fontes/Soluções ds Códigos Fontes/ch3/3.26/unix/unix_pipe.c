/**
 *
 * Programa de pipe UNIX em que o pai grava uma string em um primeiro pipe.
 * O processo filho lê essa string, inverte a caixa de cada 
 * caractere e grava o resultado em um segundo pipe.
 * O processo pai lê então esse resultado invertido no segundo pipe.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int first_pipe[2];
	int second_pipe[2];
	int i;

	if (pipe(first_pipe) == -1) {
		fprintf(stderr,"First Pipe failed");
		return 1;
	}

 	if (pipe(second_pipe) == -1) {
                fprintf(stderr,"Second Pipe failed");
                return 1;
        }


	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* fecha as extremidades não usadas de cada pipe */
		close(first_pipe[READ_END]);
		close(second_pipe[WRITE_END]);

		/* grava no pipe */
		write(first_pipe[WRITE_END], write_msg, strlen(write_msg)+1); 

		/* agora fecha a extremidade de gravação do pipe */
		close(first_pipe[WRITE_END]);

		/* lê o resultado no segundo pipe */
		read(second_pipe[READ_END], read_msg, BUFFER_SIZE);
		printf("parent read >%s<\n",read_msg);

		close(second_pipe[READ_END]);
	}
	else { /* processo filho */
		/* fecha as extremidades não usadas do pipe */
		close(first_pipe[WRITE_END]);
		close(second_pipe[READ_END]);

		/* lê no pipe */
		read(first_pipe[READ_END], read_msg, BUFFER_SIZE);
		printf("child read >%s<\n",read_msg);

		/* inverte a string */
		for (i = 0; i < strlen(read_msg); i++) {
			if (isupper(read_msg[i]))
				write_msg[i] = tolower(read_msg[i]);
			else if (islower(read_msg[i]))
				write_msg[i] = toupper(read_msg[i]);
			else
				write_msg[i] = read_msg[i];
		}

		/* grava no pipe */
		write(second_pipe[WRITE_END], write_msg, strlen(write_msg)+1);
		

		/* fecha a extremidade de gravação do pipe */
		close(first_pipe[READ_END]);
		close(second_pipe[WRITE_END]);
	}

	return 0;
}
