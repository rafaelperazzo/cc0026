/* O programa é lançado em background.
Primeiro, rode normalmente o programa. Verifique que o pai sai do wait e é concluído assim que um dos filhos
termina.
Na segunda vez, rode o programa matando o primeiro filho logo depois que o Filho2 for dormir.
Verifique que agora o pai sai do Wait(), terminando antes do Filho2. Verifique que Filho2 foi adotado pelo
init. */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
	int pid ;
	printf("\nOi, eu sou o pai PID = %d. Vou criar um filho.\n",getpid()) ;
	if ((pid=fork()) == 0) {
		printf("\tOi, eu sou o Filho1, PID = %d, PPID = %d.\n",getpid(),getppid()) ;
		printf("\tVou ficar num loop infinito.\n") ;
		for(;;) ;
	}
	else {
		printf("Oi, sou eu, o pai, de novo. Vou criar mais um filho e depois vou entrar em wait().\n") ;
		if ((pid=fork()) > 0)
			wait(NULL);
		else {
			printf("\tOi, eu sou Filho2, PID = %d, PPID = %d.\n",getpid(),getppid()) ;
			printf("\tVou dormir um pouco. Use ps -l agora\n");
			sleep(10);
			printf("\tOpa, sou o Filho2. Acordei mas estou terminando agora. Use ps -l novamente.\n") ;
		}
	}
}


