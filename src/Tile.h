#include "main.h"
#ifndef TILE_H
#define TILE_H

class Tile{
    public:
        float x, y, length, width;
        vector<float> positions;
        color_t color;
        Tile(float x, float y, float length, float width);
        void draw();
        void set_position(float x, float y);     

    private:
        VAO *object;   
};


#endif