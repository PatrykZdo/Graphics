#include "BSpline.h"
using namespace std;

int Bspline::bSpliteX(Point A,Point B,Point C,Point D,double t){
    int x;
    x=floor(((-pow(t,3)+3*pow(t,2)-3*t+1)/6*A.getX())+((3*pow(t,3)-6*pow(t,2)+4)/6*B.getX())+((-3*pow(t,3)+3*pow(t,2)+3*t+1)/6*C.getX())+(pow(t,3)/6*D.getX()));
    return x;
}

int Bspline::bSpliteY(Point A,Point B,Point C,Point D,double t){
    int y;
    y=floor(((-pow(t,3)+3*pow(t,2)-3*t+1)/6*A.getY())+((3*pow(t,3)-6*pow(t,2)+4)/6*B.getY())+((-3*pow(t,3)+3*pow(t,2)+3*t+1)/6*C.getY())+(pow(t,3)/6*D.getY()));
    return y;
}

void Bspline::drawB_spline(vector<Point> points,double t,int color,QImage *img){
    if(points.size()>3){
        for(int i=3;i<points.size();i++){
            for(double j=t*2;j<t+1;j+=t){
                int x = Bspline::bSpliteX(points[i-3],points[i-2],points[i-1],points[i],j-t);
                int y = Bspline::bSpliteY(points[i-3],points[i-2],points[i-1],points[i],j-t);
                int x1 = Bspline::bSpliteX(points[i-3],points[i-2],points[i-1],points[i],j);
                int y1 = Bspline::bSpliteY(points[i-3],points[i-2],points[i-1],points[i],j);
                Linia::drawLine(x,y,x1,y1,color,img);
            }
        }
    }
    else{
        return;
    }
}
