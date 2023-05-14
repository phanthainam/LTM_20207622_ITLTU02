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
    else printf("Connected sucessfully to server: %s \n ", inet_ntoa(server_addr.sin_addr));
    // Server request 
    char ten[64];
    char drive[26];
    int drive_size[26];
    char buf[128];

    char buf2[128];
    int ten_len;
    int ret = recv(client_socket, &ten_len, sizeof(ten_len), 0);
    if(ret > 0 ) printf("%d bytes received: %d \n", ret, ten_len);
    else printf("Failed to received: %s \n", strerror(errno));
    ret = recv(client_socket, &buf, sizeof(buf),0);
    memcpy(buf2, buf, strlen(buf));
    memcpy(ten, buf, ten_len);
    printf("%d bytes received: %s \n", ret, buf );
    //xu li du lieu
    int count = 0;
    char *str;
    str = strtok(buf+ten_len," ");
    while(str != NULL){
        str = strtok(NULL, " ");
        count++;
    }
    int num_drive = count/2;

    str = strtok(buf2 + ten_len," ");

    for(int i = 0;i < num_drive; i++){
        drive[i] = *str;
        str = strtok(NULL, " ");
    }
    for(int i = 0;i < num_drive; i++){
        drive_size[i] = atoi(str);
        str = strtok(NULL, " ");
    }

    //Hien thi ra man hinh
    printf("Ten may tinh: %s \n" , ten);
    for(int i = 0; i<num_drive; i++){
        printf("o %c: %d \n",drive[i], drive_size[i]);
    }
    
}