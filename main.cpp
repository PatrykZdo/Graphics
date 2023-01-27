#include<iostream>
#include <QApplication>

#include "Window.h"
#include "Line.h"
#include "Circle.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow w;
    w.show();
    return a.exec();
}
