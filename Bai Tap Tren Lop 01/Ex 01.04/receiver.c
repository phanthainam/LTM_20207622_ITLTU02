#include <stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    //Creating receiver socket
    int receiver_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    //Creating receiver address

    struct sockaddr_in receiver_addr;

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = INADDR_ANY;
    receiver_addr.sin_port = htons (atoi(argv[1]));

    //Bind Receiver Socket and Address together

    if(bind(receiver_socket, (struct sockaddr *) & receiver_addr, sizeof(receiver_addr))) printf("Failed to bind: %s", strerror(errno));
    else printf("Bind Sucessfully ! \n");

    //Create sender address

    struct sockaddr_in sender_addr;

    int sender_addr_len  = sizeof(sender_addr);


    // Receiving Process Handling

    char buf[256];
    int ret;
    FILE *fptr;
    char name[32];
    char new_name[32];
    ret = recvfrom(receiver_socket, name, sizeof(name), 0, (struct sockaddr *)&sender_addr, &sender_addr_len);
    name[ret] = 0;
    if(ret <= 0) printf("Failed to received: %s \n", strerror(errno));
    else printf("%d bytes received: %s \n", ret, name);

    ret = sizeof(buf);
    while(1){ 
        ret = recvfrom(receiver_socket,buf,sizeof(buf),0,(struct sockaddr *) &sender_addr,&sender_addr_len);
        buf[ret] = 0;
        sprintf(new_name,"%d", htons(sender_addr.sin_port));
        strcpy(new_name + strlen(new_name),name);
        fptr = fopen(new_name,"a");
        if(ret <= 0) printf("Failed to received: %s \n", strerror(errno));
        else printf("%d bytes received: %s \n", ret, buf);
        fwrite(buf,sizeof(char), ret, fptr);
        fclose(fptr);
    }
}

