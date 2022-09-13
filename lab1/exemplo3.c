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
        sleep(2);
        
   }
   else { //Processo pai
        int status;
        printf("[PAI]: PID %d - PPID: %d\n",getpid(),getppid());
        wait(&status);
        if (WIFEXITED(status)) {
            printf("[PAI]: Filho retornou com o codigo: %d\n",WEXITSTATUS(status));
        }
   }
   return 0;
}

