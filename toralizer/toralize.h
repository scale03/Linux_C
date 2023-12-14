/*toralize.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
          #include <sys/socket.h>   
          #include <arpa/inet.h>
          #include <netinet/in.h>
          
// socket()
// connect()
// close()
// htons()
// inet_addr()  /*string to bit ----- e.g. 192.168.10.20  242324234(8bit) ->  */

#define PROXY      "127.0.0.1"
#define PROXYPORT   9050

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

/*
+----+----+----+----+----+----+----+----+----+----+....+----+
		| VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
		+----+----+----+----+----+----+----+----+----+----+....+----+
 #bytes    1    1      2              4           variable       1*/


 struct proxy_request {
    int8 vn;     //
    int8 cd;     //
    int16 dsport;  //destination port
    int32 dstip;  //destination ip
    unsigned char userid[8];
 };
 typedef struct proxy_request Req;

 struct proxy_response {
   int8 vn;
   int8 cd;
   int16 dsport;
   int32 dstip;

 };
 typedef struct proxy_response Res;
