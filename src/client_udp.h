#ifndef CLIENT_UDP_H
#define CLIENT_UDP_H

#include "main.h"

#define PORT 8080

struct network_data{
    int sock;
    struct sockaddr_in sockinfo;
};

struct network_data prepare_client(struct network_data client);
void *send_to_server(void* client);
void *recieve_from_server(void* client);


#endif