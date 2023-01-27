QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BSpline.cpp \
    Bazier.cpp \
    Circle.cpp \
    DrawPixel.cpp \
    Ellipse.cpp \
    Line.cpp \
    Point.cpp \
    Polygon.cpp \
    ScanLine.cpp \
    main.cpp \
    window.cpp

HEADERS += \
    BSpline.h \
    Bazier.h \
    Circle.h \
    DrawPixel.h \
    Ellipse.h \
    Line.h \
    Point.h \
    Polygon.h \
    ScanLine.h \
    window.h

FORMS += \
    window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
