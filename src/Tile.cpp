#include "main.h"
#include "Tile.h"

using namespace std;

Tile::Tile(float x, float y, float length, float width){
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    
    float vertex_buffer[12] = {};
    int k = 0;
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            if(!(i && j)){
                vertex_buffer[k++]=this->x + i*width;
                vertex_buffer[k++]=this->y + j*length;
                }
            }
        }
        for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            if(i || j){
                vertex_buffer[k++]=this->x + i*width;
                vertex_buffer[k++]=this->y + j*length;
                }
            }
        }
        this->object = create2DObject(GL_TRIANGLES, 12, vertex_buffer);
}
