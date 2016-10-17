QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Squares
TEMPLATE = app

SOURCES += main.cpp \
    meinwidget.cpp \
    zeichenfelder.cpp \

HEADERS += \
    meinwidget.h \
    zeichenfelder.h \

