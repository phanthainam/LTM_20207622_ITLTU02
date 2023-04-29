#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main (){
    struct sockaddr_in client_addr;
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(client_socket == -1){
        printf("fail to create socket: %s\n", strerror(errno));
    } else printf("socket created successfully \n");
    
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9000);
    int server_socket = connect(client_socket,(struct sockaddr *)&server_addr, sizeof(server_addr));
    if (server_socket == -1){
        printf("Failed to connect to server %s : %s", inet_ntoa(server_addr.sin_addr), strerror(errno));
    }else printf("Conneted sucessfully to %s \n ", inet_ntoa(server_addr.sin_addr));
    char buf[256];
    char msg[] = "hello server, my name is Nam ";
    int sent = send(client_socket, msg, sizeof(msg), 0);
    int ret = recv(client_socket, buf,sizeof(buf), 0);
    printf("%d bytes received: %s", ret, buf);
    close(server_socket); 
}
    

    