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
    //Creating receiver socket
    int receiver_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    //Creating receiver address

    struct sockaddr_in receiver_addr;

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = INADDR_ANY;
    receiver_addr.sin_port = htons (9000);

    //Bind Receiver Socket and Address together

    if(bind(receiver_socket, (struct sockaddr *) & receiver_addr, sizeof(receiver_addr))) printf("Failed to bind: %s", strerror(errno));
    else printf("Bind Sucessfully ! /n");

    //Create Sender Address
    struct sockaddr_in sender_addr;
    int sender_addr_len = sizeof (sender_addr);

    // Receiving Process Handling
    char buf[256];
    int ret = recvfrom(receiver_socket,buf, sizeof(buf),0,(struct sockaddr *)&sender_addr, &sender_addr_len);
    if (ret <= 0) printf("Fail to received: %s", strerror(errno));
    else printf("%d bytes received: %s", ret,buf);
}