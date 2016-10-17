#include "meinwidget.h"
// Qt5 add:
#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    meinWidget w;
    w.setGeometry(0,0,1525,850);
    w.show();

    return a.exec();
}
