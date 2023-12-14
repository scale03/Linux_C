/*toralize.c*/
#include "toralize.h"

int main(int argc, char *argv[] ){
    char *host;
    int port;

   if (argc < 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        
        return -1; // return the error
    }
    host = argv[1];
    port = atoi(argv[2]);    //does it require lib?  CLI --> man atoi

}


//   in CLI :     ./toralize(arg0) 1.2.3.4(arg1) 80 (arg2)
