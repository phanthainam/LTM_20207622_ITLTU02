#include <stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main (){
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    char MSSV[9];
    char hoten[30];
    char ngaysinh[12];
    char diemtbstr[20];
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
    char times[100];
    int ret = recv(client_socket, buf, sizeof(buf),0);
    printf("%d bytes received: %s \n", ret, buf);
    buf[ret] = 0;
    // in ra màn hình
    strncpy(MSSV, buf, 8);
    MSSV[8] = 0;
    printf("MSSV: %s \n", MSSV);
    int hoten_len = ret - 9 - 16;
    strncpy(hoten, buf + 9, hoten_len);
    hoten[hoten_len] = 0;
    printf("Họ và Tên: %s \n", hoten);
    strncpy(ngaysinh, buf + 9 + hoten_len + 1, 10);
    printf("Ngay sinh: %s \n", ngaysinh);
    strncpy(diemtbstr, buf + 9 + hoten_len + 12,4);
    diemtb = atof(diemtbstr);
    printf("diem trung binh: %.2f \n", diemtb);

    // Log File
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("buf: %s \n", buf);
    sprintf(times, "%s %d-%d-%d %d:%d:%d",inet_ntoa(client_addr.sin_addr),tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("time: %s \n", times);
    char sv_log[70];
    sprintf(sv_log, "%s %s", times, buf);
    printf("Log: %s", sv_log);
    FILE *fptr;
    fptr = fopen("sv_log.txt", "a");
    fwrite(sv_log, sizeof(char), strlen(sv_log), fptr);
    }