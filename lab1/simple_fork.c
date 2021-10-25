#include <stdio.h>
#include <unistd.h>

int main(void) {
   int x;
   x = 0;
   pid_t pid = fork();
   x = 1;
   printf("I am process %ld and my x is %d\n",(long)getpid(), x);
   
   return 0;
}
