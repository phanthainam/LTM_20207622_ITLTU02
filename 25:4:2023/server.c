#include <stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>

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
    // struct sockaddr_in client_addr;
    // int client_addr_len = sizeof(client_addr);
    // int client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_len);
    
    // if (client_socket == -1) printf("Failed to accept incoming client :'( \n");
    // else printf("Accepted client: %s:%d", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    
    //Handling Client Process

    int client_list[64];
    int logged_in_client_list[64];
    memset(logged_in_client_list, 0, sizeof(logged_in_client_list));
    char client_id_list [64][64];
    char client_name_list [64][64];
    int client_number = 0;
    char send_buf[64];
    char ret_buf[64];
    int ret;
    fd_set fd_read;
    FD_ZERO(&fd_read);
    int maxdp = server_socket+1;
    while (1)
    {   // FD_SET
        FD_ZERO(&fd_read);
        FD_SET(server_socket, &fd_read);
        for(int i = 0; i < client_number; i++){
            FD_SET(client_list[i], &fd_read);
            if (client_list[i] + 1 > maxdp) maxdp = client_list[i] + 1;
        }

        //Select and FD CHECK
        select(maxdp,&fd_read,NULL,NULL,NULL);    
        if (FD_ISSET(server_socket, &fd_read)){  //Connect request
            int client_socket = accept(server_socket,NULL,NULL);
            if(client_socket == -1) printf("Failed to accept: %s", strerror(errno));
            else {
                client_list[client_number] = client_socket; 
                client_number += 1;
                char *msg = "Connected sucessfully, please log in according to format 'Client_id: Client_Name' \n";
                int sent = send(client_socket, msg, strlen(msg),0);
                printf("Client %d connected sucessfully ! \n",client_socket);
                }
        } 
        for (int i = 0; i < client_number; i ++){ //Message incoming
            if(FD_ISSET(client_list[i], &fd_read)){
                memset(ret_buf, '\0', sizeof(ret_buf));
                ret = recv(client_list[i], ret_buf, sizeof(ret_buf),0);
                if(ret == -1) printf("Failed to received: %s \n", strerror(errno));
                if(ret == 0) {
                    printf("Client %d terminated \n", client_list[i]);
                    for(int e = i; e < client_number; e ++ ){
                        client_list[e] = client_list[e+1];
                        strncpy(client_name_list[e], client_name_list[e+1], sizeof(client_name_list[e]));
                        strncpy(client_id_list[e], client_id_list[e+1], sizeof(client_name_list[e]));
                    }
                    logged_in_client_list[i] = 0;
                    client_number--;
                }
                else {
                    if (logged_in_client_list[i]==0){
                        char tmp[64];
                        int ret_num = sscanf(ret_buf, "%s%s%s",client_id_list[i],client_name_list[i], tmp);
                        if (ret_num != 2) {
                            char *msg = "Sai cu phap, vui long nhap lai ! \n";
                            send(client_list[i], msg, strlen(msg), 0);
                            break;
                        } else {
                            char *msg = "Dang nhap thanh cong ! vui long gui tin nhan !";
                            send(client_list[i], msg, strlen(msg), 0);
                            printf("%d da dang nhap thanh cong ! \n", client_list[i]);
                            logged_in_client_list[i] = 1;
                        } 
                    }else {
                        ret_buf[ret] = 0;
                        char msg[128];
                        sprintf(msg, "%s: %s", client_name_list[i], ret_buf);
                        for (int e = 0; e < client_number; e++){
                            if(client_list[e] != client_list[i]){
                                send(client_list[e], msg, strlen(msg), 0);
                            }
                        }
                        printf ("%s", msg);
                    }
                }            
            }
        }
    }
}