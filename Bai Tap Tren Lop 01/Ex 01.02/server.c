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
    // Create server addr
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(9000);

    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //Bind the socket with the created address
    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))) printf("Failed to bind: %s \n", strerror(errno));
    else printf("Binded successfully \n");

    //Put the socket into listen state
    if(listen(server_socket, 5)) printf("Fail to listen: %s \n", strerror(errno));
    else printf("Listening on: %d \n", ntohs(server_addr.sin_port));

    //Accept Incoming Client
    struct sockaddr_in client_addr;
    
    int client_addr_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_len);
    
    if (client_socket == -1) printf("Failed to accept incoming client :'( \n");
    else printf("Accepted client: %s:%d \n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    
    //Handling Client Process

    //Handling file streaming
    char *strtosrc="0123456789";
    char buf[50 - 1 +strlen(strtosrc)];
    int count = -1;
    char *src = buf;
    memset(buf,'-',strlen(strtosrc)-1);
    while (1)
    {
        int ret = recv(client_socket,buf + strlen(strtosrc) - 1, sizeof(buf) - strlen(strtosrc) + 1, 0);
        buf[ret + strlen(strtosrc) - 1] = 0;
        printf("%d bytes received: %s \n", ret, buf);
        while(src != NULL){
            src = strstr(src + strlen(strtosrc), strtosrc);
            count ++;
        }
        src = buf;
        strncpy(buf,buf + 50,9);
        if(ret < sizeof(buf) - strlen(strtosrc) + 1) break;
    }
    printf("Số lần xuất hiện '%s': %d",strtosrc ,count);
    //Searching for string
}