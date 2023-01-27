#ifndef BSPLINE_H
#define BSPLINE_H
#include <vector>

#include "Point.h"
#include "Line.h"

using namespace std;

class Bspline{
public:
    static int bSpliteX(Point,Point ,Point ,Point ,double );
    static int bSpliteY(Point,Point ,Point ,Point ,double );
    static void drawB_spline(vector<Point>,double,int,QImage*);
};
#endif // BSPLINE_H
