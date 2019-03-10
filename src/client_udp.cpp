#include "client_udp.h"

struct network_data prepare_client(struct network_data server) {
    if ((server.sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("client socket failed");
    }


    if (connect(server.sock, (struct sockaddr*)&server.sockinfo, sizeof(struct sockaddr)) < 0) {
        perror("bind client error");
    }
    return server;
}

void *send_to_server(void* serv){
    struct network_data server = *(struct network_data*)serv;
    char buffer[] = "Hello from client";
    socklen_t serv_addr_size = sizeof(struct sockaddr);
    if (sendto(server.sock, buffer, sizeof(buffer) , 0,
            (struct sockaddr *) &server.sockinfo, serv_addr_size) < 0) {
        perror("sendto error");
    }
 
}

void *recieve_from_server(void* serv){
    struct network_data server = *(struct network_data*)serv;
    char buffer[1000];
    socklen_t serv_addr_size = sizeof(struct sockaddr);
    recvfrom(server.sock, buffer, sizeof(buffer), 0,
                (struct sockaddr *) NULL, NULL);
    printf("%s\n",buffer);
}

