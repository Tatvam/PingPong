#ifndef SERVER_UDP_H
#define SERVER_UDP_H

#include "main.h"

#define PORT 8080

struct network_data{
    int sock;
    struct sockaddr_in sockinfo;
};


struct network_data prepare_server(struct network_data server);
void *send_data(void* server);
void *receive_data(void* server);
void* server_receive_loop(void *arg);
//void* server_send_loop(void *arg);


#endif