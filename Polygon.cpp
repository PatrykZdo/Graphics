#include "Polygon.h"

Polygon::Polygon(){};

Polygon::Polygon(int sX,int sY,int eX,int eY,int seq,int color,QImage *img){
    this->centerX=sX;
    this->centerY=sY;
    this->endX=eX;
    this->endY=eY;
    this->seq=seq;
    this->color=color;
    this->img=img;

    drawPolygon(centerX,centerY,endX,endY,seq,color,img);
}

Polygon::~Polygon(){};



void Polygon::drawPolygon(int sX,int sY,int eX,int eY,int seq,int color,QImage *img){
    int x=0,y=0,x1=0,y1=0;
        int a,b;
        double angle,t=0;

        a=abs(sX-eX);
        b=abs(sY-eY);
        angle=(2*M_PI)/seq;
        for (int i = 0; i < seq; ++i) {
                x =floor(a * cos(t));
                y =floor(b * sin(t));
                x1=floor(a * cos(t+angle));
                y1=floor(b * sin(t+angle));
                Linia::drawLine((x+sX-10),(y+sY-10),(x1+sX-10),(y1+sY-10),color,img);
                t+=angle;
            }
}
