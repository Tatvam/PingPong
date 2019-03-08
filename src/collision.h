#ifndef COLLISION_H
#define COLLISION_H

#include "main.h"
#include "Tile.h"
#include "ball.h"

void CollisionDetection(Tile *player1, Tile *player2, Ball *ball);
void CollisionResolution(int which_player, Ball* ball);
int check_who_lose(Ball *ball);
// int check_if_player_lose(struct Player *player);

#endif