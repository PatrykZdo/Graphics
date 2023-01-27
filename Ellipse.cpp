#include "Ellipse.h"

Ellipse::Ellipse(){};

Ellipse::Ellipse(int startX,int startY,int endX,int endY,int color,QImage *img){
    this->centerX=startX;
    this->centerY=startY;
    this->endX=endX;
    this->endY=endY;
    this->color=color;

    drawEllipse(centerX,centerY,getA(centerX,endX),getB(centerY,endY),color,img);
}

Ellipse::~Ellipse(){};

                                                                //sX= start X position, eX= end X position
int Ellipse::getA(int sX,int eX){
    return abs(sX-eX);
}

int Ellipse::getB(int sY,int eY){
    return abs(sY-eY);
}

int Ellipse::getCenterX(){
    return this->centerX;
}

int Ellipse::getCenterY(){
    return this->centerY;
}



void Ellipse::drawEllipse(int centerX,int centerY,int a,int b,int color,QImage *img){
    int x,y;
    for( y=0;y<b;y++){
            x=(a*sqrt((b+y)*(b-y)))/b;
            Pixel::drawPixel((x+centerX),(y+centerY),color,img);
            Pixel::drawPixel((-x+centerX),(-y+centerY),color,img);
            Pixel::drawPixel((-x+centerX),(y+centerY),color,img);
            Pixel::drawPixel((x+centerX),(-y+centerY),color,img);
        }
    for(x=0;x<a;x++){
            y=pow(b,2)-((pow(x,2)*pow(b,2))/pow(a,2));
            y=sqrt(y);
            Pixel::drawPixel((x+centerX),(y+centerY),color,img);
            Pixel::drawPixel((-x+centerX),(-y+centerY),color,img);
            Pixel::drawPixel((-x+centerX),(y+centerY),color,img);
            Pixel::drawPixel((x+centerX),(-y+centerY),color,img);
        }

}
