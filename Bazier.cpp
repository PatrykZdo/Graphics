#include "Bazier.h"


int Bazier::bazierX(Point A,Point B,Point C,Point D,double t){
    int x;
    x=floor(pow(1-t,3)*A.getX()+3*pow(1-t,2)*t*B.getX()+3*(1-t)*pow(t,2)*C.getX()+pow(t,3)*D.getX());
    return x;
}

int Bazier::bazierY(Point A,Point B,Point C,Point D,double t){
    int y;
    y=floor(pow(1-t,3)*A.getY()+3*pow(1-t,2)*t*B.getY()+3*(1-t)*pow(t,2)*C.getY()+pow(t,3)*D.getY());
    return y;
}

void Bazier::drawBazier(vector<Point> points,double t,int color,QImage* img){
    if(points.size()>3){
        for(int i=3;i<points.size();i++){
            if(i%3==0){
                for(double j=t*2;j<t+1;j+=t){
                    int x=Bazier::bazierX(points[i-3],points[i-2],points[i-1],points[i],j-t);
                    int y=Bazier::bazierY(points[i-3],points[i-2],points[i-1],points[i],j-t);
                    int x1=Bazier::bazierX(points[i-3],points[i-2],points[i-1],points[i],j);
                    int y1=Bazier::bazierY(points[i-3],points[i-2],points[i-1],points[i],j);
                    Linia::drawLine(x,y,x1,y1,color,img);
                }
            }
        }
    }
    else{
        return;
    }
}
