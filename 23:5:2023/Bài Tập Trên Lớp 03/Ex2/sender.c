#include <stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){

    // Create sender socket
    int sender_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Create receiver addr
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = INADDR_ANY;
    receiver_addr.sin_port = htons(9000);
    
    //Handling Sending Process
    char *msg = "hello receiver";
    sendto(sender_socket,msg,strlen(msg),0, (struct sockaddr *) &receiver_addr, sizeof(receiver_addr));
    
}