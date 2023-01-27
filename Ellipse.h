#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <cstdlib>
#include "DrawPixel.h"

class Ellipse{
private:
    int centerX;
    int centerY;
    int endX;
    int endY;
    int color;
    QImage *img;

public:
    Ellipse();
    Ellipse(int,int,int,int,int,QImage*);
    ~Ellipse();

    int getA(int,int);
    int getB(int,int);
    int getCenterX();
    int getCenterY();


    static void drawEllipse(int,int,int,int,int,QImage*);



};

#endif // ELLIPSE_H
