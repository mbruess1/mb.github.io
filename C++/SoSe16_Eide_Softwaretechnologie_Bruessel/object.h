 #include <QGraphicsScene>
 #include <QPainter>
 #include <QStyleOption>
 #include <math.h>
#include <QtGui>
#include <QMessageBox>
using namespace std;

class Object : public QGraphicsItem
{
public:
    Object();
    Q_OBJECT;


    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
//    void advance(int step);
    void paintEvent(QPaintEvent *event);

private:
    vector<struct myDrawingObject *> objects;
    QTimer *timer;
    int increment;

    int x, startx;
    int y, starty;
    int phase;
    bool clockwork;
    int speed;
    enum Qt::GlobalColor color, color2; //http://doc.qt.io/qt-5/qt.html#GlobalColor-enum

//    qreal angle;
//    qreal speed;
//    qreal mouseEyeDirection;
//    QColor color;
};
