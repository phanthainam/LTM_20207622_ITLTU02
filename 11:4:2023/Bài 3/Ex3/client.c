#include <stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    int server_socket = connect(client_socket,(struct sockaddr *)&server_addr, sizeof(server_addr));
    if(server_socket == -1){
        printf("Fail to Connect to Server %s : %d, reason being %s \n", inet_ntoa(server_addr.sin_addr), htons(server_addr.sin_port), strerror(errno));
    } else printf("Connected sucessfully to %s : %d \n", inet_ntoa(server_addr.sin_addr), htons(server_addr.sin_port));
    char MSSV[9];
    char hoten[30];
    char ngaysinh[12];
    float diemtb;
    int count = 1;
    printf("Nhập họ tên của sinh viên số %d: ", count);
    fgets(hoten, sizeof(hoten), stdin);
    hoten[strlen(hoten)-1]=0;
    printf("Nhập MSSV của sinh viên số %d: ", count);
    scanf("%s", MSSV);
    printf("Nhập ngày sinh của sinh viên số %d: ", count);
    scanf ("%s", ngaysinh);
    printf("nhập điểm trung bình của sinh viên số %d: ", count);
    scanf("%f",&diemtb);
    char buf[50];
    sprintf(buf, "%s %s %s %.2f",MSSV, hoten, ngaysinh, diemtb);
    int sent = send(client_socket, buf, strlen(buf),0);
    if (sent > 0){
        printf("%d bytes sent successfully !", sent);
    } else printf("Failed to sent: %s !", strerror(errno));
}