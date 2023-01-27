#include "ScanLine.h"
#include <iostream>
using namespace std;

int ScanLine::minY(vector<Point> P){
    int min=P[0].getY();
    for(int i=1;i<P.size();i++){
        if(P[i].getY()<min){
            min=P[i].getY();
        }
    }
    return min;
}

int ScanLine::maxY(vector<Point> P){
    int max=P[0].getY();
    for(int i=1;i<P.size();i++){
        if(P[i].getY()>max){
            max=P[i].getY();
        }
    }
    return max;
}


void ScanLine::crossPoint(vector<Point> P,vector<int> &X,int y){
     int x;
     for(int i=0;i<P.size();i++){\
        if(i<P.size()-1){
            if((P[i].getY() > y && P[i+1].getY() <= y) || (P[i].getY() <= y && P[i+1].getY() > y)){
                if(P[i].getX()-P[i+1].getX()==0){
                    X.push_back(P[i].getX());
                }
                else{
                float a=(P[i].getY() - P[i+1].getY())/(float)(P[i].getX()-P[i+1].getX());
                float b=P[i+1].getY() - (a * P[i+1].getX());
                x=floor((y-b)/a);
                X.push_back(x);
                }
                //cout<<P[i].getX()<<" i:"<<i<<endl;
            }
        }
        else if(i==P.size()-1){
            if((P[i].getY() > y && P[0].getY() <= y) || (P[i].getY() <= y && P[0].getY() > y)){
                if(P[i].getX()-P[i+1].getX()==0){
                    X.push_back(P[i].getX());
                }
                else{
                float a=(P[i].getY() - P[0].getY())/(float)(P[i].getX()-P[0].getX());
                float b=P[0].getY() - (a * P[0].getX());
                x=floor((y-b)/a);
                X.push_back(x);
                }
                //cout<<P[i].getX()<<" i:"<<i<<endl;
            }
        }
     }
}


void ScanLine::pointsSorter(vector<int> &xPoints){
    for(int i=0;i<xPoints.size();i++){
        for(int j=i;j<xPoints.size();j++){
            if(xPoints[i]>xPoints[j]){
                int pom=xPoints[i];
                xPoints[i]=xPoints[j];
                xPoints[j]=pom;

            }
            //cout<<xPoints[i]<<"    "<<xPoints[j]<<endl;
        }
    }
}

void ScanLine::drawScanLine(vector<Point> P,QImage *img){
    srand(time(NULL));
    int color=rand()%125;
    for(int y=ScanLine::minY(P);y<ScanLine::maxY(P);y++){
       vector<int> X;
       ScanLine::crossPoint(P,X,y);
       ScanLine::pointsSorter(X);
       for(int i=0;i<X.size();i+=2){
           Linia::drawLine(X[i],y,X[i+1],y,color,img);
           //cout<<y<<"       "<<X[i]<<" "<<X[i+1]<<endl;
       }
       //cout<<endl;
       X.clear();
    }
}
