#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int a = 0;
    if (fork() == 0) {
        a = a + 5;
        printf("%d\n", a);
    }
    else {
        a = a -5;
        printf("%d\n", a);
    }
}