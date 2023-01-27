#ifndef SCANLINE_H
#define SCANLINE_H
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Point.h"
#include "Line.h"


using namespace std;

class ScanLine{
public:
    static int  minY(vector<Point>);
    static int maxY(vector<Point>);
    static void crossPoint(vector<Point>,vector<int>&,int);
    static void pointsSorter(vector<int>&);
    static void drawScanLine(vector<Point>,QImage *);
};


#endif // SCANLINE_H
