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
    char send_buf[256];
    char ret_buf[256];
    fd_set fd_read;
    while(1){
        //Attach sockets to fd_set
        FD_ZERO(&fd_read);
        FD_SET(client_socket,&fd_read);
        FD_SET(STDIN_FILENO, &fd_read);

        //Select
        select(client_socket+1,&fd_read,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO, &fd_read)){
            fgets(send_buf,sizeof(send_buf),stdin);
            int sent = send(client_socket, send_buf,strlen(send_buf),0);
        }
        if(FD_ISSET(client_socket, &fd_read)){
            int ret = recv(client_socket, ret_buf, sizeof(ret_buf),0);
            ret_buf[ret] = 0;
            if (ret > 0) printf("%s",ret_buf);
            fflush(stdout);
    }
}
}