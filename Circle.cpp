#include "Circle.h"

Circle::Circle(){};

Circle::Circle(int cX,int cY,float R,int color,QImage *img){
    this->centerX=cX;
    this->centerY=cY;
    this->R=R;
    this->img=img;
    this->color=color;

    drawCircle(this->centerX,this->centerY,this->R,this->color,this->img);
}

Circle::~Circle(){};


int Circle::getCenterX(){
    return this->centerX;
}

int Circle::getCenterY(){
    return this->centerY;
}

float Circle::getRadius(){
    return this->R;
}


void Circle::drawCircle(int cX,int cY,float R,int color,QImage *img){
    int y=0,x=0;
    for(x;x<=floor(R/sqrt(2));x++){
        y=sqrt(pow(R,2)-pow(x,2));
        Pixel::drawPixel((x+cX),(y+cY),color,img);
        Pixel::drawPixel((-x+cX),(-y+cY),color,img);
        Pixel::drawPixel((x+cX),(-y+cY),color,img);
        Pixel::drawPixel((-x+cX),(y+cY),color,img);
        Pixel::drawPixel((y+cX),(-x+cY),color,img);
        Pixel::drawPixel((y+cX),(x+cY),color,img);
        Pixel::drawPixel((-y+cX),(x+cY),color,img);
        Pixel::drawPixel((-y+cX),(-x+cY),color,img);
    }
}
