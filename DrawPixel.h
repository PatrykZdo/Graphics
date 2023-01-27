#ifndef DRAWPIXEL_H
#define DRAWPIXEL_H

#include "QImage"

class Pixel{
private:

    int x;
    int y;
    int color;
    QImage *img;

public:

    Pixel();
    Pixel(int,int,int,QImage*);
    ~Pixel();

    static void drawPixel(int,int,int,QImage*);

};

#endif // DRAWPIXEL_H
