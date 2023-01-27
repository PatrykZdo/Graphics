
#include <iostream>
// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji

#include <QApplication>

// Dolaczamy plik naglowkowy klasy QWidget,
// Jest to klasa bazowa wszystkich elementow GUI
#include <QWidget>

// Dolaczamy plik naglowkowy klasy QPushButton
// (standardowy przycisk)
#include <QPushButton>

// Dolaczamy plik naglowkowy klasy QGroupBox
// (do grupowania komponentow GUI)
#include <QGroupBox>

// QPainter to klasa umozliwiajaca niskopoziomowe rysowanie
// na elementach GUI
#include <QPainter>

// QImage to klasa pozwalajaca na niezalezna od sprzetu reprezentacje obrazu.
// Pozwala na bezposredni dostep do poszczegolnych pikseli,
// Bedziemy jej uzywali do tworzenia i przechowywania
// naszych rysunkow
#include <QImage>

// QMouseEvent to klasa obslugujaca zdarzenia zwiazane z myszka
// klikniecia, ruch myszka itp.
#include <QMouseEvent>
#include <QSlider>
#include <QLCDNumber>
#include <QCheckBox>
#include <vector>
#include <math.h>
#include <iostream>
#include "Point.h"
#include "DrawPixel.h"
#include "BSpline.h"
#include "ScanLine.h"

using namespace std;
// MyWindow jest podklasa klasy QWidget
class MyWindow : public QWidget
{
    // Makro ktore musimy dodac jezeli definiujemy wlasne sygnaly lub sloty
    Q_OBJECT
public:
    // Typowa deklaracja konstruktora w Qt.
    // Parametr "parent" okresla rodzica komponenetu.
    // W przypadku naszej klasy parametr ten wskazuje na null
    // co oznacza, ze komponenet nie ma rodzica, jest to
    // komponenet najwyzszego poziomu
    MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:

    friend class Pixel;

    // Pole przechowujace obrazek
    QImage *img;
    QImage *bg;
    QImage *bazierPoints;
    QImage *onlyLines;
    QImage *b_splinePoints;

    // Przyciski
    QPushButton *drawLine;
    QPushButton *drawCircle;
    QPushButton *drawEllipse;
    QPushButton *drawPolygon;
    QPushButton *drawBezierCurve;
    QPushButton *drawBSpline;
    QPushButton *scanLine;
    QPushButton *paint;
    QPushButton *cleanButton;
    QPushButton *exitButton;

    QSlider *slider;            //Slider i Panel LCD dla wielokata
    QLCDNumber *screen;

    QCheckBox *punkty;
    QCheckBox *B_splineVisible;

    // Grupa przyciskow
    QGroupBox *grupa;
    QGroupBox *grupaWielokat;
    QGroupBox *grupaBazier;
    QGroupBox *grupaB_spline;
    QGroupBox *grupaScanLine;

    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int poczX;
    int poczY;
    int startX;
    int startY;
    int endX;
    int endY;

    int color;
    int pointColor;

    int counter;
    int changePoint;
    char pointer;
    bool spr;
    vector<Point> Points;
    vector<Point> pointsB_spline;
    vector<Point> ScanLinePoints;



    // Deklaracje funkcji
    void czysc();
    void clean(QImage *);
    void rysuj1();
    void rysuj2();
    void copy(QImage*,QImage*);



    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void slot_czysc();
    void slot_line();
    void slot_circle();
    void slot_ellipse();
    void slot_polygon();
    void slot_BezierCurve();
    void slot_BSpline();
    void slot_ScanLine();
    void pointsVisible();
    void painting();
    void changeValue();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

};

