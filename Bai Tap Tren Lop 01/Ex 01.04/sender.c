#include <stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char *argv[]){

    // Create sender socket
    int sender_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Create receiver addr
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = INADDR_ANY;
    receiver_addr.sin_port = htons(9000);
    
    //Sending Message
    FILE *fptr;
    fptr = fopen(argv[1],"r");
    char buf[256];
    int count;
    int ret;
    int sent;

    sent = sendto(sender_socket, argv[1],strlen(argv[1]), 0, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

    while (!feof(fptr))
    {
        if(feof(fptr)){
           ret = fread(buf,sizeof(char),ftell(fptr) - count * sizeof(buf), fptr);
        } else ret = fread(buf,sizeof(char),sizeof(buf), fptr);
        sent = sendto(sender_socket,buf,ret,0,(struct sockaddr *)&receiver_addr, sizeof(receiver_addr));
        if(sent <= 0) printf("Failed to sent: %s", strerror(errno));
        else printf("%d bytes sent %s \n", sent, buf);
    }

    //Handling Sending Process

    
}