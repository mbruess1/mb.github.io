TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    bibliographielib.cpp \
    titelsatzlib.cpp

HEADERS += \
    bibliographie.h \
    titelsatz.h
