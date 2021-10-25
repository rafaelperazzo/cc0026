#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void sighup();
void sigint();
void sigquit();

int main(void) {
   pid_t pid = fork();
   if (pid<0) {
       printf("Falha ao criar o processo!\n");
   }
   else if (pid==0) { //Processo filho
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        for (;;);
   }
   else { //Processo pai
        printf("[PAI]: PID %d - PPID: %d\n",getpid(),getppid());
        printf("\nPARENT: sending SIGHUP\n\n");
        kill(pid, SIGHUP);
  
        sleep(3); /* pause for 3 secs */
        printf("\nPARENT: sending SIGINT\n\n");
        kill(pid, SIGINT);
        sleep(1);
        kill(pid, SIGINT);
  
        sleep(3); /* pause for 3 secs */
        printf("\nPARENT: sending SIGQUIT\n\n");
        kill(pid, SIGQUIT);
        sleep(5);

   }
   return 0;
}

void sighup() {
    signal(SIGHUP, sighup); /* reset signal */
    printf("CHILD: I have received a SIGHUP\n");
}

void sigint() {
    signal(SIGINT, sigint); /* reset signal */
    printf("CHILD: I have received a SIGINT\n");
}

void sigquit() {
     printf("My DADDY has Killed me!!!\n");
     exit(0);
}