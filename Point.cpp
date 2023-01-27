#include "Point.h"

Point::Point(int x,int y,int color){
    this->posX=x;
    this->posY=y;
    this->color=color;
    this->zmiana=false;
}

Point::~Point(){};


int Point::getX(){
    return this->posX;
}

int Point::getY(){
    return this->posY;
}


void Point::changingPos(int posX,int posY){
    this->posX=posX;
    this->posY=posY;
}


void Point::drawPoint(int x,int y,int color,QImage *img){
    for (int i=x-5;i<x+5;i++){
        for(int j=y-5;j<y+5;j++){
            Pixel::drawPixel(i,j,color,img);
        }
    }
}
