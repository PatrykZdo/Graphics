
#include "Window.h"
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "Point.h"
#include "DrawPixel.h"
#include "Bazier.h"

// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>
#include <QSlider>
#include <iostream>

using namespace std;

// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Rysowanie pikseli w Qt");

    //Zmieniamy rozmiar okna
    resize(800,700);

    // Ustawiamy wymiary obrazka i wspolrzedne jego
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 600;
    wys = 600;
    poczX = 25;
    poczY = 25;


    counter=0;
    changePoint=-1;
    color=155;
    pointColor=100;

                                                                                                    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
                                                                                                    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
                                                                                                    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);
    bg = new QImage(szer,wys,QImage::Format_RGB32);
    bazierPoints = new QImage(szer,wys,QImage::Format_RGB32);
    onlyLines = new QImage(szer,wys,QImage::Format_RGB32);
    b_splinePoints = new QImage(szer,wys,QImage::Format_RGB32);
    clean(img);
    clean(bg);
    clean(bazierPoints);
    clean(onlyLines);
                                                                                                    // Tworzymy grupe elementow
                                                                                                    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);

                                                                                                    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+250));
                                                                                               // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

                                                                                                    // Tworzymy 4 przyciski
    drawLine = new QPushButton("Linia");
    drawCircle = new QPushButton("Kolo");
    drawEllipse = new QPushButton("Elipsa");
    drawPolygon= new QPushButton("Wielokat");
    drawBezierCurve=new QPushButton("Krzywa Beziera");
    drawBSpline=new QPushButton("B-Spline");
    scanLine=new QPushButton("Scan Line");
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");

                                                                   // Dodajemy przyciski do layoutu
    boxLayout->addWidget(drawLine);
    boxLayout->addWidget(drawCircle);
    boxLayout->addWidget(drawEllipse);
    boxLayout->addWidget(drawPolygon);
    boxLayout->addWidget(drawBezierCurve);
    boxLayout->addWidget(drawBSpline);
    boxLayout->addWidget(scanLine);
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);

                                                                                                    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);


                                                                                                    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
                                                                                                    // ze slotem quit(). qApp to globalny counteraznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
                                                                                                    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));

    connect(drawLine,SIGNAL(clicked()),this,SLOT(slot_line()));

    connect(drawCircle,SIGNAL(clicked()),this,SLOT(slot_circle()));

    connect(drawEllipse,SIGNAL(clicked()),this,SLOT(slot_ellipse()));

    connect(drawPolygon,SIGNAL(clicked()),this,SLOT(slot_polygon()));

    connect(drawBezierCurve,SIGNAL(clicked()),this,SLOT(slot_BezierCurve()));

    connect(drawBSpline,SIGNAL(clicked()),this,SLOT(slot_BSpline()));

    connect(scanLine,SIGNAL(clicked()),this,SLOT(slot_ScanLine()));




    grupaWielokat=new QGroupBox("katy",this);                                                   //Grupa wyswietlajaca Slider oraz Panel LCD
    grupaWielokat->setGeometry(QRect(poczX+szer+poczX,poczY+300,800-szer-2*poczX,poczY+70));

    QVBoxLayout *groupTwoBox = new QVBoxLayout;

    slider=new QSlider(Qt::Horizontal,this);
    slider->setMinimum(3);
    slider->setMaximum(100);

    screen=new QLCDNumber(slider->value(),this);

    groupTwoBox->addWidget(slider);
    groupTwoBox->addWidget(screen);

    grupaWielokat->setLayout(groupTwoBox);
    grupaWielokat->setVisible(false);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(changeValue()));




    grupaBazier=new QGroupBox("Bazier Ustawienia",this);
    grupaBazier->setGeometry(QRect(poczX+szer+poczX,poczY+300,800-szer-2*poczX,poczY+70));

    QVBoxLayout *groupPoint = new QVBoxLayout;

    punkty=new QCheckBox("Pokazuj Punkty",this);

    groupPoint->addWidget(punkty);

    grupaBazier->setLayout(groupPoint);
    grupaBazier->setVisible(false);
    punkty->setCheckState(Qt::CheckState(2));

    connect(punkty,SIGNAL(stateChanged(int)),this,SLOT(pointsVisible()));



    grupaB_spline=new QGroupBox("B_spline Ustawienia",this);
    grupaB_spline->setGeometry(QRect(poczX+szer+poczX,poczY+300,800-szer-2*poczX,poczY+70));

    QVBoxLayout *groupB_spline = new QVBoxLayout;

    B_splineVisible=new QCheckBox("Pokazuj Punkty",this);

    groupB_spline->addWidget(B_splineVisible);

    grupaB_spline->setLayout(groupB_spline);
    grupaB_spline->setVisible(false);
    B_splineVisible->setCheckState(Qt::CheckState(2));

    connect(B_splineVisible,SIGNAL(stateChanged(int)),this,SLOT(pointsVisible()));



    grupaScanLine = new QGroupBox("Malowanie",this);
    grupaScanLine->setGeometry(QRect(poczX+szer+poczX,poczY+300,800-szer-2*poczX,poczY+70));

    QVBoxLayout *ScanLine = new QVBoxLayout;

    paint=new QPushButton("Zamaluj",this);

    ScanLine->addWidget(paint);

    grupaScanLine->setLayout(ScanLine);
    grupaScanLine->setVisible(false);

    connect(paint,SIGNAL(clicked(bool)),this,SLOT(painting()));

}

MyWindow::~MyWindow()
{
    delete img;
    delete bg;
}
                                                                          // Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
                                                                            // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

                                                                            // Rysuje obrazek "img" w punkcie (poczX,poczY)
                                                                            // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);

}



void MyWindow::slot_czysc()
{
    czysc();                        //slot CZYSC
    update();
}

void MyWindow::slot_line()
{
    copy(onlyLines,img);
    this->pointer='L';                     //slot LINIA
    grupaWielokat->setVisible(false);
    grupaBazier->setVisible(false);
    grupaB_spline->setVisible(false);
    grupaScanLine->setVisible(false);
    update();
}

void MyWindow::slot_circle()
{
    copy(onlyLines,img);
    this->pointer='K';                      //slot KOLO
    grupaWielokat->setVisible(false);
    grupaBazier->setVisible(false);
    grupaB_spline->setVisible(false);
    grupaScanLine->setVisible(false);
    update();
}

void MyWindow::slot_ellipse(){
    copy(onlyLines,img);
    this->pointer='E';                      //slot ELIPSA
    grupaWielokat->setVisible(false);
    grupaBazier->setVisible(false);
    grupaB_spline->setVisible(false);
    grupaScanLine->setVisible(false);

    update();
}

void MyWindow::slot_polygon(){
    copy(onlyLines,img);
    this->pointer='P';
    grupaBazier->setVisible(false);
    grupaScanLine->setVisible(false);
    grupaWielokat->setVisible(true);               //slot WIELOKAT
    slider->setValue(3);
    screen->display(slider->value());
    grupaB_spline->setVisible(false);
    update();

}

void MyWindow::slot_BezierCurve(){
    if(punkty->checkState()==2){
        copy(bg,bazierPoints);
        for(int i=0;i<Points.size();i++){
            Point::drawPoint(Points[i].getX(),Points[i].getY(),pointColor,bazierPoints);
        }
        copy(bazierPoints,img);

    }
    else{
        copy(onlyLines,img);
    }
    this->pointer='B';
    grupaWielokat->setVisible(false);
    grupaBazier->setVisible(true);
    grupaB_spline->setVisible(false);
    grupaScanLine->setVisible(false);
    update();
}

void MyWindow::slot_BSpline(){
    if(B_splineVisible->checkState()==2){
        copy(bg,b_splinePoints);
        for(int i=0;i<pointsB_spline.size();i++){
            Point::drawPoint(pointsB_spline[i].getX(),pointsB_spline[i].getY(),pointColor,b_splinePoints);
        }
        copy(b_splinePoints,img);
    }
    else{
        copy(onlyLines,img);
    }
    this->pointer='S';
    grupaWielokat->setVisible(false);
    grupaBazier->setVisible(false);
    grupaB_spline->setVisible(true);
    grupaScanLine->setVisible(false);
    update();
}

void MyWindow::slot_ScanLine(){
    this->pointer='Q';                     //slot LINIA
    grupaWielokat->setVisible(false);
    grupaBazier->setVisible(false);
    grupaB_spline->setVisible(false);
    grupaScanLine->setVisible(true);
    update();
}

void MyWindow::painting(){
    if(ScanLinePoints.size()>2){
        ScanLine::drawScanLine(ScanLinePoints,onlyLines);
        copy(onlyLines,img);
        ScanLinePoints.clear();
        update();
    }
    copy(onlyLines,bg);
}

void MyWindow::changeValue(){
    screen->display(slider->value());       //slot changeValue do slidera
}

void MyWindow::czysc()
{
    clean(img);
    clean(bg);
    clean(bazierPoints);
    clean(onlyLines);

    Points.clear();
    pointsB_spline.clear();
}

void MyWindow::clean(QImage *img){
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
}

void MyWindow::pointsVisible(){
    switch(this->pointer){
    case'B':{
            if(punkty->checkState()==2){
                if(Points.size()>0){
                    copy(bg,bazierPoints);
                    for(int i=0;i<Points.size();i++){
                            Point::drawPoint(Points[i].getX(),Points[i].getY(),pointColor,bazierPoints);
                        }
                    copy(bazierPoints,img);
                    }
                }
            else{
                copy(onlyLines,img);
            }
            update();
        }
        break;
    case'S':{
            if(B_splineVisible->checkState()==2){
                if(pointsB_spline.size()>0){
                    copy(bg,b_splinePoints);
                    for(int i=0;i<pointsB_spline.size();i++){
                            Point::drawPoint(pointsB_spline[i].getX(),pointsB_spline[i].getY(),pointColor,b_splinePoints);
                        }
                    copy(b_splinePoints,img);
                    }
                }
            else{
                copy(onlyLines,img);
            }
            update();
        }
        break;
    }
}

void MyWindow::copy(QImage* img,QImage* bg){
    int x=img->width();
    int y=img->height();
    for(int i=0;i<x;i++){
        for (int j=0;j<y;j++){
            bg->bits()[szer*4*j + 4*i]=img->bits()[szer*4*j + 4*i];
            bg->bits()[szer*4*j + 4*i+1]=img->bits()[szer*4*j + 4*i];   //funkcja kopjujaca "obrazy"
            bg->bits()[szer*4*j + 4*i+2]=img->bits()[szer*4*j + 4*i];
        }
    }
}



void MyWindow::mousePressEvent(QMouseEvent *event)
{
    this->startX = event->x()-poczX;
    this->startY= event->y()-poczY;

    switch(this->pointer){
    case 'B':{
            if(Points.size()>0){
                for(int i=0;i<Points.size();i++){
                    if(startX<=Points[i].getX()+5 && startX>=Points[i].getX()-5 && startY<=Points[i].getY()+5&& startY>=Points[i].getY()-5){
                        Points[i].zmiana=true;
                        changePoint=i;
                        Bazier::drawBazier(Points,0.001,255,bg);
                        break;
                    }
                }
            }
        }
        break;
    case 'S':{
            if(pointsB_spline.size()>0){
                for(int i=0;i<pointsB_spline.size();i++){
                    if(startX<=pointsB_spline[i].getX()+5 && startX>=pointsB_spline[i].getX()-5 && startY<=pointsB_spline[i].getY()+5&& startY>=pointsB_spline[i].getY()-5){
                        changePoint=i;
                        pointsB_spline[i].zmiana=true;
                        Bspline::drawB_spline(pointsB_spline,0.1,255,bg);
                        break;
                    }
                }
            }
    }
        break;


    case 'Q':{
            copy(onlyLines,img);
            if(ScanLinePoints.size()>0){
                vector<Point>::iterator it=ScanLinePoints.begin()+ScanLinePoints.size()-1;
                        Linia::drawLine(it->getX(),it->getY(),startX,startY,0,img);
                        Linia::drawLine(startX,startY,ScanLinePoints.begin()->getX(),ScanLinePoints.begin()->getY(),0,img);
            }
            update();
        }
        break;



    default:
        changePoint=-1;

    }

}

void MyWindow::mouseReleaseEvent(QMouseEvent *event){
    this->endX = event->x()-poczX;
    this->endY= event->y()-poczY;
    switch(this->pointer){
    case 'L':
            Linia::drawLine(startX,startY,endX,endY,color,onlyLines);
            copy(onlyLines,img);
            copy(onlyLines,bg);
        break;



    case 'K':{
            float R=sqrt(pow((endX-startX),2)+pow((endY-startY),2));
            Circle::drawCircle(startX,startY,R,color,onlyLines);
            copy(onlyLines,img);
            copy(onlyLines,bg);
            }
            break;



    case 'E':{
            int a=abs(startX-endX);
            int b=abs(startY-endY);
            Ellipse::drawEllipse(startX,startY,a,b,color,onlyLines);
            copy(onlyLines,img);
            copy(onlyLines,bg);
            }
        break;



    case 'P':{
            Polygon::drawPolygon(startX,startY,endX,endY,slider->value(),color,onlyLines);
            copy(onlyLines,img);
            copy(onlyLines,bg);
            }
        break;



    case 'B':{

            if(changePoint!=-1 && Points[changePoint].zmiana==true){
                Points[changePoint].changingPos(endX,endY);
                Bazier::drawBazier(Points,0.001,color,onlyLines);
                if(punkty->checkState()==2){
                    copy(onlyLines,bazierPoints);
                    for(int i=0;i<Points.size();i++){
                        Point::drawPoint(Points[i].getX(),Points[i].getY(),pointColor,bazierPoints);
                    }
                    copy(bazierPoints,img);
                }
                else{
                    copy(onlyLines,img);

                }

                Points[changePoint].zmiana=false;
                changePoint=-1;
            }
            else{
                 Points.push_back(Point(endX,endY,pointColor));
                 Bazier::drawBazier(Points,0.001,color,onlyLines);
                 copy(onlyLines,bg);
                 if(punkty->checkState()==2){
                     copy(onlyLines,bazierPoints);
                     for(int i=0;i<Points.size();i++){
                         Point::drawPoint(Points[i].getX(),Points[i].getY(),pointColor,bazierPoints);
                     }
                     copy(bazierPoints,img);
                 }
                 else{
                     copy(onlyLines,img);

                 }
            }
            copy(onlyLines,bg);
        }
        break;



    case 'S':{
            if(changePoint!=-1 && pointsB_spline[changePoint].zmiana==true){
                pointsB_spline[changePoint].changingPos(endX,endY);
                Bspline::drawB_spline(pointsB_spline,0.1,color,onlyLines);
                if(B_splineVisible->checkState()==2){
                    copy(onlyLines,b_splinePoints);
                    for(int i=0;i<pointsB_spline.size();i++){
                        Point::drawPoint(pointsB_spline[i].getX(),pointsB_spline[i].getY(),pointColor,b_splinePoints);
                    }
                    copy(b_splinePoints,img);
                }
                else{
                    copy(onlyLines,img);

                }

                pointsB_spline[changePoint].zmiana=false;
                changePoint=-1;
            }
            else{
                pointsB_spline.push_back(Point(endX,endY,pointColor));
                Bspline::drawB_spline(pointsB_spline,0.1,color,onlyLines);
                copy(onlyLines,bg);
                if(B_splineVisible->checkState()==2){
                    copy(onlyLines,b_splinePoints);
                    for(int i=0;i<pointsB_spline.size();i++){
                        Point::drawPoint(pointsB_spline[i].getX(),pointsB_spline[i].getY(),pointColor,b_splinePoints);
                    }
                    copy(b_splinePoints,img);
                }
                else{
                    copy(onlyLines,img);

                }
            }
            copy(onlyLines,bg);
        }
        break;



    case 'Q':{
            if(ScanLinePoints.size()>0){
                vector<Point>::iterator it=ScanLinePoints.begin()+ScanLinePoints.size()-1;
                        Linia::drawLine(it->getX(),it->getY(),endX,endY,0,onlyLines);
                        copy(onlyLines,bg);
                        Linia::drawLine(endX,endY,ScanLinePoints.begin()->getX(),ScanLinePoints.begin()->getY(),0,bg);
            }
            ScanLinePoints.push_back(Point(endX,endY,0));
            update();
        }
        break;


    default:
            Pixel::drawPixel(endX,endY,color,onlyLines);
            copy(onlyLines,img);
            copy(onlyLines,bg);

    }
    update();
}










void MyWindow::mouseMoveEvent(QMouseEvent *event){
    this->endX = event->x()-poczX;
    this->endY= event->y()-poczY;


    switch(this->pointer){
    case 'L':{
            copy(bg,onlyLines);
            Linia::drawLine(startX,startY,endX,endY,color,onlyLines);
            copy(onlyLines,img);
            }
       break;



    case 'K':{
            copy(bg,onlyLines);
            float R=sqrt(pow((endX-startX),2)+pow((endY-startY),2));
            Circle::drawCircle(startX,startY,R,color,onlyLines);
            copy(onlyLines,img);
            }
        break;



    case 'E':{
            copy(bg,onlyLines);
            int a=abs(startX-endX);
            int b=abs(startY-endY);
            Ellipse::drawEllipse(startX,startY,a,b,color,onlyLines);
            copy(onlyLines,img);
            }
        break;



    case 'P':{
            copy(bg,onlyLines);
            Polygon::drawPolygon(startX,startY,endX,endY,slider->value(),color,onlyLines);
            copy(onlyLines,img);
            }
        break;



    case 'B':{
        copy(bg,onlyLines);
            if(changePoint!=-1 && Points[changePoint].zmiana==true){
                Points[changePoint].changingPos(endX,endY);
                Bazier::drawBazier(Points,0.001,color,onlyLines);
                if(punkty->checkState()==2){
                    copy(onlyLines,bazierPoints);
                    for(int i=0;i<Points.size();i++){
                        Point::drawPoint(Points[i].getX(),Points[i].getY(),pointColor,bazierPoints);
                    }
                    copy(bazierPoints,img);
                }
                else{
                    copy(onlyLines,img);
                }
            }
            else{
                Points.push_back(Point(endX,endY,pointColor));
                Bazier::drawBazier(Points,0.001,color,onlyLines);
                if(punkty->checkState()==2){
                    copy(onlyLines,bazierPoints);
                    for(int i=0;i<Points.size();i++){
                        Point::drawPoint(Points[i].getX(),Points[i].getY(),pointColor,bazierPoints);
                    }
                    copy(bazierPoints,img);
                }
                else{
                    copy(onlyLines,img);
                }
                Points.pop_back();
            }
        }
        break;



    case 'S':{
        copy(bg,onlyLines);
            if(changePoint!=-1 && pointsB_spline[changePoint].zmiana==true){
                pointsB_spline[changePoint].changingPos(endX,endY);
                Bspline::drawB_spline(pointsB_spline,0.1,color,onlyLines);
                if(B_splineVisible->checkState()==2){
                    copy(onlyLines,b_splinePoints);
                    for(int i=0;i<pointsB_spline.size();i++){
                        Point::drawPoint(pointsB_spline[i].getX(),pointsB_spline[i].getY(),pointColor,b_splinePoints);
                    }
                    copy(b_splinePoints,img);
                }
                else{
                    copy(onlyLines,img);
                }
            }
            else{
                pointsB_spline.push_back(Point(endX,endY,pointColor));
                Bspline::drawB_spline(pointsB_spline,0.1,color,onlyLines);
                if(B_splineVisible->checkState()==2){
                    copy(onlyLines,b_splinePoints);
                    for(int i=0;i<pointsB_spline.size();i++){
                        Point::drawPoint(pointsB_spline[i].getX(),pointsB_spline[i].getY(),pointColor,b_splinePoints);
                    }
                    copy(b_splinePoints,img);
                }
                else{
                    copy(onlyLines,img);
                }
                pointsB_spline.pop_back();
            }
        }
        break;


    case 'Q':{
            copy(onlyLines,img);
            if(ScanLinePoints.size()>0){
                vector<Point>::iterator it=ScanLinePoints.begin()+ScanLinePoints.size()-1;
                        Linia::drawLine(it->getX(),it->getY(),endX,endY,0,img);
                        Linia::drawLine(endX,endY,ScanLinePoints.begin()->getX(),ScanLinePoints.begin()->getY(),0,img);
            }
            update();
        }
        break;


    default:
            Pixel::drawPixel(endX,endY,color,onlyLines);
            copy(onlyLines,img);

    }
    update();
}


