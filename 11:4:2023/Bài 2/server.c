#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

    if (argc != 4){
        printf("Wrong input");
        return 0;
    }
    uint16_t port_addr = atoi(argv[1]);
    char *greet = argv[2];
    char *clientmsg = argv[3];
    struct sockaddr_in server_addr; // tao cau truc dia chi
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port = htons(port_addr);
    int server_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if (server_socket==-1){
        printf("fail to create socket: %s \n ", strerror(errno));
    } else printf("socket created sucessfully ! \n");

     if (bind(server_socket,(struct sockaddr *)&server_addr, sizeof(server_addr))){
        printf("failed to bind: %s \n", strerror(errno));
     } else printf("binded sucessfully ! \n");

    if (listen(server_socket,5)){
        printf("failed to listen: %s \n", strerror(errno));
    } else printf("listen sucessfully on %d ! \n",ntohs(server_addr.sin_port) );

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int client_socket = accept(server_socket,(struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket == -1){
        printf("Accept failed: %s", strerror(errno));
    } else {printf("Accepted Client %s \n",inet_ntoa(client_addr.sin_addr));}
    FILE *fptr;
    fptr = fopen(greet,"r");
    char filebuf[256];
    fgets(filebuf, sizeof(filebuf), fptr);
    fclose(fptr);
    int sent = send(client_socket, filebuf, sizeof(filebuf), 0);
    char buf[10];
    int ret;
    int sum = 0;
    fopen(clientmsg, "a");
    while (1)
    {
        ret = recv(client_socket, buf, sizeof(buf)-1, 0);
        if(ret <= 0){
            break;
        }
        if(ret < sizeof(buf)){
            buf[ret]=0;
        }
        buf[ret]= 0;
        printf("%d bytes received: %s \n", ret, buf);
        sum += ret;
        fwrite(buf, sizeof(char),ret,fptr);
    }
    printf("%d", sum);
}