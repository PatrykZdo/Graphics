#ifndef BAZIER_H
#define BAZIER_H
#include <vector>

#include "Point.h"
#include "Line.h"

using namespace std;


class Bazier{
public:
  static int bazierX(Point,Point,Point,Point,double);
  static int bazierY(Point,Point,Point,Point,double);
  static void drawBazier(vector<Point>,double,int,QImage*);
};
#endif // BAZIER_H
