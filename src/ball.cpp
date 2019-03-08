#include "main.h"
#include "ball.h"

using namespace std;

void Ball::move(){
    float dt = 0.005;
    if(this->stuck){
    //if(this->stuck){
        // Move the Ball
        this->x =this->x + this->Vx * dt ;
        this->y =this->y + this->Vy * dt ;
       // cout<<this->x<< "  "<< this->y<<endl;
        // x axis 
        // if(this->x <= -1.0f){
        //     this->Vx = -this->Vx;
        //     this->x = -1.0f ; 
        // }else if((this->x + this->width) >=1.0f){
        //     this->Vx = -this->Vx;
        //     this->x = 1.0f-this->width;
        // }
        //    Y axis 
        if(this->y >= .85f){
            this->Vy = -this->Vy;
            this->y = .85f ; 
        }else if((this->y - this->length) <= -1.0f){
            this->Vy = -this->Vy;
            this->y = -1.0f+this->length;
      //  }
        }
    }
    this->draw();
}