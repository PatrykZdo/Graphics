#include "DrawPixel.h"

Pixel::Pixel(int x,int y,int color,QImage *img){
    this->x=x;
    this->y=y;
    this->img=img;
    this->color=color;

    drawPixel(this->x,this->y,this->color,img);
};

void Pixel::drawPixel(int x,int y,int color, QImage *img){
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();
    if(color>255){
        color=255;
    }
    else if(color<0){
        color=0;
    }

    if(x>=szer||x<0||y>=wys||y<0){
        return ;
    }

    ptr[szer*4*y + 4*x]=color;
    ptr[szer*4*y + 4*x + 1] = color;
    ptr[szer*4*y + 4*x + 2] = color;
}
