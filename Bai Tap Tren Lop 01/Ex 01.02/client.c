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
    //Creating client_socket
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //Creating server address

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons (9000);


    //Connect Client to Server

    int server_socket = connect(client_socket, (struct sockaddr *) &server_addr,sizeof(server_addr));
    if (server_socket == -1) printf(" Failed to connect: %s \n ", strerror(errno));
    else printf("Connected sucessfully to server: %s \n", inet_ntoa(server_addr.sin_addr));
    // Server request handling

    //Handling file streaming
    char readbuf[50];
    FILE *fptr;
    fptr = fopen("soict.txt", "r");
    int ret = sizeof(readbuf);
    int count = 0;
    while (!feof(fptr))
    {
        ret = fread(readbuf,sizeof(char), sizeof(readbuf), fptr);  
        count ++;
        readbuf[ret] = 0;
        int sent = send(client_socket, readbuf, ret, 0);
        if(sent <= 0)printf("Fail to send: %s \n", strerror(errno));
        else printf("%d bytes sent: %s \n", sent, readbuf);
    }    
}