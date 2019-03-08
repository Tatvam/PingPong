#include "collision.h"
#include"ball.h"
#include "Tile.h"
#include "main.h"
using namespace std;

// AABB (Axis-Aligned Bounding Box) Collision Detection Algorithm


void CollisionResolution(int wp, Tile* player1, Tile* player2, Ball* ball){
    if(wp == 1){
        ball->Vx = -ball->Vx;
        ball->x = player1->x + player1->width ; 
           
    }else {
        ball->Vx = -ball->Vx;
        ball->x = player2->x;
    }
}

void CollisionDetection(Tile *player1, Tile *player2, Ball *ball){

    bool collisionX1 = ball->x <= (player1->x + player1->width);
    bool collisionX2 = (ball->x + ball->width) >= player2->x;


    bool collisionY1 = (ball->y <= (player1->y + player1->length)) && ball->y >=player1->y;
    bool collisionY2 = (ball->y <= (player2->y + player2->length)) && ball->y >=player2->y;

    if(collisionX2 && collisionY2)
    cout<<"collision happened at "<<ball->x<<" "<<ball->y<<endl;

    if(collisionX1 && collisionY1){
        CollisionResolution(1, player1, player2, ball);
    }else if(collisionX2 && collisionY2){
        CollisionResolution(2, player1, player2, ball);
    }

}

int check_who_lose(Ball *ball){
    if(ball->x <= -1.0f){
        return 1;
    }else if ((ball->x + ball->width) >=1.0f){
        return 2;
    }else{
        return 0;
    }
}