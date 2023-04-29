#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    //kiểm soát đầu vào
    if (argc != 3){
        printf("lỗi đầu vào ");
        return 0;
    }
    char *ip_addr = argv[1];
    char *port_addr = argv [2];
    printf("IP: %s \n Port: %s \n ", ip_addr, port_addr );

    int client_socket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);//khai báo socket client
    if(client_socket == -1){
        printf("socket failed to be created");
    }
    else printf("socket created successfully");

    struct sockaddr_in server_addr; // khai cấu trúc địa chỉ server
    server_addr.sin_port =  htons(atoi(port_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr= inet_addr(ip_addr);

    int server_socket = connect(client_socket, (struct sockaddr *)&server_addr,sizeof(server_addr)); // connect với địa chỉ máy chủ khai báo ở trên
    if (server_socket==-1){
        printf("Failed to connect: %s \n", strerror(errno));
    } else printf ("Connect successfully\n");

    char *msg = "Hello Server";
    if(send(client_socket,msg,strlen(msg),0)==-1){
        printf("Failed to send: %s", strerror(errno));
    }
    else printf("Send successfully !");   
}