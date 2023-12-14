//╽╽╽╽╽╽╽╽  ╽╽╽╽╽╽╽╽╽   #  ╽╽╽     ╽  ╽╽╽╽
//  ###     ╽╽       ╽╽╽          ╽╽       
  //      ╽╽          ╽╽   ╻╻╻    ╽ #    ╽
//╽╽╽     ╽    ╒╒╒     ╽  ╻╻╻╻╻   ╽  ╁╁╁  
//  ╽     ╽   ╒╒╒╒╒  #   ╻╻╻╻╻    ╽╽ ╁╁╁  
//            ╒╒╒3╒   #  ╻╻╻╻╻     @╽ ╁╁╁╁
//╁╁╁╁╁╁      ╒╒╒╒╒   # ╻╻╻╻╻  #    ╽  ╁2╁
//    ╁╁╁╁@@╁╁╁╁╒╒   ╽## ╻╻╻╻╻╻╻╻   ╽╽ ╁╁╁
//##          ╁╁╁  #####  ╻╻╻╻╻╻╻╻   ╽ ╁╁╁
//  ####       #####  ###    ╻╻╻╻╻   ╽ ╁╁╁
//    
//╁╁        ###  ╁╁╁╁      ##╻╻╻╻╻╻     ╽ 
//╁      ####    ╁╁╁  #  ╽  # ╻╻╻╻      ╽ 
//     ##        ╁╁╁  #  ╽╽ ##      #   ╽╽
//    #          ╁╁╁  ##   ╽ ##  ╽  #    ╽
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//To create a socket, you call the `socket()` function, passing in three arguments:

//1. The address family (`AF_INET` for IPv4 or `AF_INET6` for IPv6)
//2. The socket type (`SOCK_STREAM` for TCP or `SOCK_DGRAM` for UDP)
//3. Protocol number (usually 0)

#define PORT 8080
#define BUFFER_SIZE 256

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    //create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
          perror("socket");
	  exit (1);

    }
    //set up server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET , "127.0.0.1", &serv_addr.sin_addr);
    

    //Bind the socket to the address and port
    if(bind(sockfd, (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0) {
       perror("bind");
       exit(1);
     } 

     printf("server listening on port %d...\n", PORT);

     //listen for incoming connections
     if (listen(sockfd, 3) < 0) {
	perror("listen");
		exit(1);
     }    
  
     printf("server listening on port %d...\n", PORT);


    while(1) {
	//accept incoming connection
        newsockfd = accept (sockfd, (struct sockaddr *)&client_addr, &client_len);
        if (newsockfd < 0) {
        perror("accept");
        exit(1);
                 }

        printf("connection accepted from client\n");


     //receive data from the client 
     int bytes_read = read(newsockfd, buffer, BUFFER_SIZE - 1);
     if (bytes_read < 0) {
	perror("read");
	close(newsockfd);
	continue;
     }
     buffer[bytes_read] = '\0'; //null-terminate the string
				//
     printf("Received message from client: %s\n", buffer);

     // send response back to the client
     write(newsockfd,"Hello Client! This the server response.\n" , 43);

     //close the connection
     close(newsockfd);
     }
     return 0;
     }
