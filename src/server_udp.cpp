#include "server_udp.h"
#include "main.h"
struct network_data prepare_server(struct network_data server) {
    if ((server.sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
    }
    
    int opt = 1;

    if( setsockopt(server.sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    if (bind(server.sock, (struct sockaddr*)&server.sockinfo, sizeof(struct sockaddr)) < 0) {
        perror("bind server error");
    }
    return server;
}

void *send_data(void* serv) {
    struct network_data* client = (struct network_data*)serv;
    socklen_t addr_size = sizeof(struct sockaddr);
    char buffer[] = "Hello from server";
    sendto(client->sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client->sockinfo, addr_size);
}

void *receive_data(void* serv) {
    struct network_data* client = (struct network_data*)serv;
    socklen_t addr_size = sizeof(struct sockaddr);
    int buffer[1000];
    recvfrom(client->sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client->sockinfo, &addr_size);
    printf("%s\n",buffer);
}

 

// void init_players_tab() {
//     int i;
//     for (i = 0; i < MAX_PLAYERS; i++) {
//         players_server[i].position.w = PLAYER_WIDTH;
//         players_server[i].position.h = PLAYER_HEIGHT;
//         players_server[i].position.x = SPAWN_X;
//         players_server[i].position.y = SPAWN_Y;
//     }
// }

// void* server_receive_loop(void *arg) {
//     int socket = *((int *) arg);
//     int client_pos = 0;
//     struct sockaddr_in client_addr;
//     int16_t tab[4];
//     init_players_tab();
//     while (1) {
//         client_addr = receive_data(socket, tab);
//         client_pos = addr_pos_in_tab(client_addr, clients_addresses, number_of_connected_clients);
//         if (its_an_old_client(client_pos)) {
//             int16_t keys = tab[1];
//             player_from_key_state(&players_server[client_pos], keys);
//             if(players_server[client_pos].shoot && !players_server[client_pos].reloading) {
//                 struct Bullet temp;
//                 temp.position.x = players_server[client_pos].position.x;
//                 temp.position.y = players_server[client_pos].position.y;
//                 temp.position.w = BULLET_WIDTH;
//                 temp.position.h = BULLET_HEIGHT;
//                 temp.face = players_server[client_pos].face;
//                 if (temp.face == 1) {
//                     temp.position.x += PLAYER_WIDTH;
//                 } else {
//                     temp.position.x -= BULLET_WIDTH;
//                 }
//                 temp.player_id = client_pos;
//                 push_element(&bullets_server, &temp, sizeof(struct Bullet));
//             }
//             players_server[client_pos].reloading = players_server[client_pos].shoot;
//         }
//         if (tab[0] == -1 && client_pos < MAX_PLAYERS) {
//             add_adr_to_list(client_pos, &client_addr);
//             int16_t tab[3];
//             tab[0] = -1;
//             tab[1] = client_pos;
//             send_data(socket, clients_addresses[client_pos], tab, 3);
//         }
//         usleep(50);
//     }
// }

// int get_bullet_array(struct node *list, int16_t **array) {
//     int n = 0;
//     struct node *temp = list;
//     while (temp != NULL) {
//         n++;
//         temp = temp->next;
//     }
//     *array = malloc(sizeof(int16_t) + (n * 2 * sizeof(int16_t)));
//     (*array)[0] = -2;
//     int i = 0; 
//     temp = list;
//     while (temp != NULL && i < n) {
//         (*array)[1 + (i * 2)] = ((struct Bullet*) temp->data)->position.x;
//         (*array)[2 + (i * 2)] = ((struct Bullet*) temp->data)->position.y;
//         i++;
//         temp = temp->next;
//     }
//     return n;
// }

// void* server_send_loop(void *arg) {
//     int socket = *((int *) arg);
//     int16_t tab[3];
//     struct timeval start, stop;
//     double time_interval;
//     int killer;
//     while (1) {
//         gettimeofday(&start, NULL);
//         int i, j;
//         move_bullets(&bullets_server);
//         for (i = 0; i < number_of_connected_clients; i++) {
//             move_player(&players_server[i]);
//             if (check_if_player_dies(&players_server[i], &bullets_server, &killer)) {
//                 players_server[i].position.x = SPAWN_X;
//                 players_server[i].position.y = SPAWN_Y;
//                 players_server[i].deaths++;
//                 players_server[killer].kills++;
//             }
//         }
//         int16_t *bullet_array = NULL;
//         int bullets_n = get_bullet_array(bullets_server, &bullet_array);
//         for (i = 0; i < number_of_connected_clients; i++) {
//             for (j = 0; j < number_of_connected_clients; j++) {
//                 tab[0] = j;
//                 tab[1] = players_server[j].position.x;
//                 tab[2] = players_server[j].position.y;
//                 tab[3] = players_server[j].kills;
//                 tab[4] = players_server[j].deaths;
//                 send_data(socket, clients_addresses[i], tab, 5);
//                 usleep(20);
//             }
//             send_data(socket, clients_addresses[i], bullet_array, 1 + (bullets_n * 2));
//             usleep(20);
//         }
//         free(bullet_array);
//         gettimeofday(&stop, NULL);
//         time_interval = (double) (stop.tv_usec - start.tv_usec);
//         if ((double) (stop.tv_usec - start.tv_usec) > 0) {
//             time_interval = (double) (stop.tv_usec - start.tv_usec);
//         }
//         usleep(FRAME_TIME - time_interval);
//     }
// }

