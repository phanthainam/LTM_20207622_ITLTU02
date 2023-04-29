#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

int main(){
    struct sockaddr_in serveraddr; //khai bao cau truc dia chi server
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port=htons(9000);

    int server_socket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);//khai báo socket server
    if(server_socket == -1){
        printf("socket failed to be created");
    }
    else printf("socket created successfully");
    if (bind(server_socket, (struct sockaddr *)&serveraddr, sizeof(serveraddr)))
    {
        printf("Failed to Bind \n");
    }
    else printf("Bind successfully \n");
    if (listen(server_socket, 5)){
        printf("Failed to listen: %s \n",strerror(errno));
    }
    else printf("listened successfully ! ");

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int acp_socket = accept(server_socket,(struct sockaddr *)&client_addr,&client_addr_len); 
    if(acp_socket==-1){
        printf("accept failed: %s", strerror(errno));
    } else printf("accepted client: %s\n", inet_ntoa(client_addr.sin_addr));

    char buf[256];
    do
    {
       int ret = recv(acp_socket, buf, sizeof(buf), 0);
    if (ret > 0){
        printf("%d bytes received: %s \n", ret, buf);
        }
    } while (1);
    } 
