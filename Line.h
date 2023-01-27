#ifndef LINE_H
#define LINE_H
#include "DrawPixel.h"

class Linia{
private:
    int startX;
    int startY;
    int endX;
    int endY;
    int color;
    QImage *img;

public:
    Linia();
    Linia(int,int,int,int,int,QImage*);
    ~Linia();

    int getStartX();
    int getStartY();
    int getEndX();
    int getEndY();

    static void drawLine(int,int,int,int,int,QImage*);

};

#endif // LINE_H
