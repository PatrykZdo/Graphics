#ifndef CIRCLE_H
#define CIRCLE_H
#include "DrawPixel.h"

class Circle{
private:
    int centerX;
    int centerY;
    int color;
    float R;
    QImage *img;

public:
    Circle();
    Circle(int,int,float,int,QImage *);
    ~Circle();

    int getCenterX();
    int getCenterY();
    float getRadius();

    static void drawCircle(int,int,float,int,QImage *);
};

#endif // CIRCLE_H
