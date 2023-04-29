#include <stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (){
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    char MSSV[9];
    char hoten[30];
    char ngaysinh[12];
    char diemtbstr[6];
    float diemtb;
    
    int server_socket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if(server_socket==-1){
        printf("Fail to create Socket: %s \n", strerror(errno));
    } else printf("Socket created sucessfully ! \n");

    if(bind(server_socket,(struct sockaddr *)&server_addr, sizeof(server_addr))){
        printf("Failed to bind: %s \n", strerror(errno));
    } else printf("Binded sucessfully ! \n");
    if(listen(server_socket, 5)){
        printf("Failed to listen: %s", strerror(errno));
    }  else printf ("Listened sucessfully on %d \n", htons(server_addr.sin_port));
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *)& client_addr, &client_addr_len);
    if (client_socket == -1){
        printf("Fail to accept: %s", strerror(errno));
    } else printf("Accepted sucessfully client %s:%d \n", inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));
    char buf[50];
    int ret = recv(client_socket, buf, sizeof(buf),0);
    printf("%d bytes received: %s \n", ret, buf);
    strncpy(MSSV, buf, 8);
    MSSV[8] = 0;
    printf("MSSV: %s \n", MSSV);
    int hoten_len = ret - 9 - 16;
    strncpy(hoten, buf + 9, hoten_len);
    printf("Họ và Tên: %s \n", hoten);
    strncpy(ngaysinh, buf + 9 + hoten_len + 1, 10);
    printf("Ngay sinh: %s \n", ngaysinh);
    strcpy(diemtbstr, buf + 9 + hoten_len + 12);
    diemtb = atof(diemtbstr);
    printf("diem trung binh: %.2f", diemtb);
    
    }