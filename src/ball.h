#include "main.h"
#include "Tile.h"
#ifndef BALL_H
#define BALL_H

class Ball : public Tile{
    public:
        float Vx;
        float Vy;
        bool stuck;
        Ball(float x, float y, float length, float width, float Vx, float Vy) 
            : Tile (x, y, length, width)
            {
                this->Vx = Vx;
                this->Vy = Vy;
                this->stuck = 1;
            }
        void move();
};


#endif