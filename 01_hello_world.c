
#include <unistd.h>

int main ( void ) {
    const char * msg = " Hello World !\n";
    write ( STDOUT_FILENO , msg , 13) ;
    return 0;
}