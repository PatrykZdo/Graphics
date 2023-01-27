#ifndef POLYGON_H
#define POLYGON_H
#include "DrawPixel.h"
#include "Line.h"

class Polygon{
private:
    int centerX;
    int centerY;
    int endX;
    int endY;
    int seq;
    int color;
    QImage *img;

public:
    Polygon();
    Polygon(int,int,int,int,int,int,QImage*);
    ~Polygon();

    int getCenterX();
    int getCenterY();
    int getEndX();
    int getEndY();
    int getSequence();  //get number of sequences

    static void drawPolygon(int,int,int,int,int,int,QImage*);

};

#endif // POLYGON_H
