#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
   pid_t pid = fork();
   if (pid<0) {
       printf("Falha ao criar o processo!\n");
   }
   else if (pid==0) { //Processo filho
        printf("[FILHO]: PID %d - PPID: %d\n",getpid(),getppid());
        printf("Vou dormir um pouco...\n");
        sleep(60);
   }
   else { //Processo pai
        int status;
        printf("[PAI]: PID %d - PPID: %d\n",getpid(),getppid());
        wait(&status);
        if (WIFSIGNALED(status)) {
            printf("[PAI]: Filho (%d) terminou devido a um sinal: %d\n",pid,WTERMSIG(status));
        }
        else {
            printf("[PAI]: Filho (%d) nao terminou devido a um sinal\n",pid);
        }
   }
   return 0;
}

