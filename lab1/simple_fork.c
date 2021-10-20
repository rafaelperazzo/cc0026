#include <stdio.h>
#include <unistd.h>

int main(void) {
   int x;

   x = 0;
   long pid = fork();
   x = 1;
   
   if (pid==0) {
      printf("I am process %ld and my x is %d\n",(long)getpid(), x);
   }
   else {
      printf("I am process %ld and my x is %d\n",(long)getpid(), x);
   }
   
   return 0;
}
