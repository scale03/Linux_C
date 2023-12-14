#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define IP "" // define the IP address to connect to
#define PORT 80 //  (HTTP default port)

int main() {
    int s;
    struct sockaddr_in sock; // socket struct address declaration

    char buf[512]; // buffer declaration for received data
    char *data = "HEAD / HTTP/1.0\r\n\r\n"; // define the HTTP HEAD request data

    s = socket(AF_INET, SOCK_STREAM, 0); // create a socket
    if (s < 0) {
        printf("socket() error\n"); // print an error message if socket creation fails
        return -1;
    }

    sock.sin_addr.s_addr = inet_addr(IP); // set the IP address of the socket
    sock.sin_port = htons(PORT); // set the port number of the socket
    sock.sin_family = AF_INET; // set the address family (IPv4)

    if (connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr_in)) != 0) {
        printf("connect() error\n"); // print an error message if connection fails
        close(s); // close the socket
        return -1; // exit with error code
    }

    write(s, data, strlen(data)); // send the HTTP HEAD request to the server
    read(s, buf, 511); // receive data from the server (up to 511 bytes)
    close(s); // close the socket

    printf("\n%s\n", buf); // print the received data

    return 0; // exit with success code
}



