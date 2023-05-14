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

    //a. Đóng gói dữ liệu
    char buf[128];
    char ten[64];  
    char drive[26]; 
    int drive_size[26];
    int num_of_drive = 0;
    int ten_len;
    printf("Vui long nhap ten may tinh: ");
    fgets(ten, sizeof(ten), stdin);
    ten[strlen(ten) -1] = 0;
    int check = 1;
    while (check == 1)
    {   
        printf("Vui long nhap ten o dia: ");
        scanf ("%c", &drive[num_of_drive]);
        getchar();
        printf("Vui long nhap kich thuoc: "); 
        scanf("%d", &drive_size[num_of_drive]);
        getchar();
        num_of_drive ++;
        printf("Do you wish to continue ? 1/0 \n ");
        scanf("%d",&check);
        getchar();
        if(check == 0) break;
    }
    ten[strlen(ten)] = NULL;
    strcpy(buf,ten);

    ten_len = strlen(ten);

    printf("Number of drive: %d \n", num_of_drive);

    for(int i = 0; i < num_of_drive; i++){
        strcat(buf, " ");
        strncat(buf, &drive[i], 1);
    }
    for(int i=0; i < num_of_drive; i++){
        sprintf(buf,"%s %d", buf, drive_size[i]);
    }
    printf("%s \n", buf);

    //b. Gửi dữ liệu
    int sent = send(client_socket, &ten_len, sizeof(int),0);
    if(sent > 0) printf("%d bytes sent: %d \n", sent, ten_len);
    else printf("Fail to sent: %s", strerror(errno));
    sent = send(client_socket,buf,strlen(buf),0);
    if (sent > 0) printf("%d bytes sent: %s", sent,buf);
    else printf("Failed to sent: %s", strerror(errno));
    
}