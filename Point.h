#include "DrawPixel.h"

#ifndef POINT_H
#define POINT_H


class Point{
private:
    int posX;
    int posY;
    int color;

public:
    bool zmiana;

    Point(int,int,int);
    ~Point();

    int getX();
    int getY();

    void changingPos(int,int);

    static void drawPoint(int,int,int,QImage*);
};


#endif // POINT_H
