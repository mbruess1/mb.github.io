#include <QtGui>
#include <QMessageBox>
#include "zeichenfelder.h"
using namespace std;
#include <stdio.h>
#include <math.h>
#define PI 3.14159265

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    increment=0;

    placeObject(); //draw squares
}

zeichenFeld::~zeichenFeld()
{
    for (vector<struct myDrawingObject *>::iterator pos=objects.begin();pos!=objects.end();pos++)
        delete *pos;
}

//detect collision
bool zeichenFeld::rectangleCollision(const struct myDrawingObject *position1, float width1, float height1,
                                        const struct myDrawingObject *position2, float width2, float height2)
{
      if (position1->x+width1 <= position2->x) return false; // "other" is on the far right
      if (position2->x+width2 <= position1->x) return false; //"other" is on the far left
      if (position1->y+height1 <= position2->y) return false; // "other" is up
      if (position2->y+height2 <= position1->y) return false; // "other" is down
      return true;
}

//detect approximation
bool zeichenFeld::rectangleApproximation(const struct myDrawingObject *position1, float width1, float height1,
                                            const struct myDrawingObject *position2, float width2, float height2)
{
      if (position1->x+width1+50 <= position2->x-50) return false;
      if (position2->x+width2+50 <= position1->x-50) return false;
      if (position1->y+height1+50 <= position2->y-50) return false;
      if (position2->y+height2+50 <= position1->y-50) return false;
      return true;
}

//paintEvent
void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter;
    vector<struct myDrawingObject *>::iterator pos;
    vector<struct myDrawingObject *>::iterator one;
    vector<struct myDrawingObject *>::iterator two;

    int x,y, startx, starty, phase, speed, i;
    enum Qt::GlobalColor color;
    bool clockwise;
    double angle;
    bool meet=false, collide=false;
    enum Qt::GlobalColor colorchoice[]={Qt::red, Qt::green, Qt::blue, Qt::black}; //normal
    enum Qt::GlobalColor colorchoice2[]={Qt::black, Qt::blue, Qt::red, Qt::green}; //at approximation
//    enum Qt::GlobalColor colorchoice2[]={Qt::white, Qt::white, Qt::white, Qt::white};   //test

    for (pos=objects.begin(); pos!=objects.end(); pos++)
    {
        for (one=objects.begin(); one!=objects.end(); one++)
        {
            if(pos!=one)
            {
                //check for collision
                collide=rectangleCollision((*pos), 50, 50, (*one), 50, 50);
                if(collide==true)
                {
                    //change direction
                    if ((*one)->clockwise==true)
                        (*one)->clockwise=false;
                    else
                        (*one)->clockwise=true;
                }

                //adjust fill color by approximation
                if(meet!=true)
                    meet=rectangleApproximation((*pos), 50, 50, (*one), 50, 50);

                if(meet==true)
                    for(two=objects.begin(), i=0; two!=objects.end(); two++, i++)
                        (*two)->color=colorchoice2[i];
                else
                    for(two=objects.begin(), i=0; two!=objects.end(); two++, i++)
                        (*two)->color=colorchoice[i];
            }
        }
    }

    for (pos=objects.begin(); pos!=objects.end(); pos++)
    {
        phase=(*pos)->phase;
        speed=(*pos)->speed;
        x=(*pos)->x;
        y=(*pos)->y;
        startx=(*pos)->startx;
        starty=(*pos)->starty;
        clockwise=(*pos)->clockwise;
        angle=(*pos)->angle;

        //movement of squares
        if (increment)
        {
            //circular path
            if (*pos==objects.at(2)) //choose which square should move on a circular path
            {
                if (clockwise==true)
                    angle = angle - 0.1 * speed; // - clockwise
                else
                    angle = angle + 0.1 * speed; // + anti-clockwise
                double r= 250;
                double alpha = (225 - angle) * PI / 180.0;
                double beta = angle * PI / 180.0;
                double nextX = r * cos ( alpha - beta);
                double nextY = r * sin (alpha - beta);
                x= int(nextX) + startx + sqrt(250*125);
                y= int(nextY) + starty + sqrt(250*125);
            //square path
            } else {
                if(clockwise==true)
                {
                    switch(phase)
                    {
                    case 0:
                        if (x<(startx+500))
                            x+=speed;
                        else
                            phase=1;
                        break;
                    case 1:
                        if (y<(starty+500))
                            y+=speed;
                        else
                            phase=2;
                        break;
                    case 2:
                        if (x>startx)
                            x-=speed;
                        else
                            phase=3;
                        break;
                    case 3:
                        if (y>starty)
                            y-=speed;
                        else
                            phase=0;
                        break;
                    }
                }
                else //anti-clockwise
                {
                    switch(phase)
                    {
                    case 2:
                        if (x<(startx+500))
                            x+=speed;
                        else
                            phase=1;
                        break;
                    case 3:
                        if (y<(starty+500))
                            y+=speed;
                        else
                            phase=2;
                        break;
                    case 0:
                        if (x>startx)
                            x-=speed;
                        else
                            phase=3;
                        break;
                    case 1:
                        if (y>starty)
                            y-=speed;
                        else
                            phase=0;
                        break;
                    }
                }
            }
        }
        (*pos)->phase=phase;
        (*pos)->speed=speed;
        (*pos)->x=x;
        (*pos)->y=y;
        (*pos)->clockwise=clockwise;
        (*pos)->angle=angle;
    }

    //draw
    painter.begin( this );
    painter.setPen( QPen(Qt::black, 3) );
    for (pos=objects.begin(), i=0; pos!=objects.end(); pos++, i++)
    {
            color=(*pos)->color;
            painter.setBrush(color);
            painter.drawRect((*pos)->x,(*pos)->y,50,50);
    }
    painter.end();
}

//serialize
void zeichenFeld::serialize(QFile &file)
{
    vector<struct myDrawingObject *>::iterator pos;

    QTextStream out(&file);

    out << "MeinZeichnungsFormat" << endl;
    for (pos=objects.begin();pos!=objects.end();pos++)
    {
        out << "p "<< increment << " " << (*pos)->phase << " " << (*pos)->angle << " "
            << (*pos)->clockwise << " " << (*pos)->speed << " " << (*pos)->color << " "
            << (*pos)->x << " " << (*pos)->startx << " "
            << (*pos)->y << " " << (*pos)->starty << "\n";
    }
}

//deserialize
void zeichenFeld::deserialize(QFile &file)
{
    vector<struct myDrawingObject *>::iterator pos;

    char c;
    int colorvalue;
    int clockwise;
    QString test;

    QTextStream in(&file);

    in >> test;
    if (test != "MeinZeichnungsFormat")
    {
        QMessageBox::warning(this, tr("Formatfehler"),
                             tr("Das ist keine Zechnungsdatei!"),QMessageBox::Ok);
        return;
    }

    in >> c; // Leerstellen werden vom '>>' Operator 'konmsumiert'; Zeilenenden nicht.

    while (in.status() == QTextStream::Ok)
    {
        in >> c;
        if (in.status() == QTextStream::ReadPastEnd)
            break;

        if (c!='p')
        {
            QMessageBox::warning(this, tr("Objektfehler"),
                                 tr("Folgender Objekttyp ist unbekannt: ") + c,QMessageBox::Ok);
            return;
        }

        for (pos=objects.begin();pos!=objects.end();pos++)
        {
            in >> increment >> (*pos)->phase >> (*pos)->angle >> clockwise >> (*pos)->speed >> colorvalue
                                             >> (*pos)->x >> (*pos)->startx
                                             >> (*pos)->y >> (*pos)->starty >> c;
            in >> c;
            if (colorvalue == 7)
                (*pos)->color=Qt::red;
            else if (colorvalue == 8)
                (*pos)->color=Qt::green;
            else if (colorvalue == 9)
                (*pos)->color=Qt::blue;
            else if (colorvalue == 2)
                (*pos)->color=Qt::black;
            else
                (*pos)->color=Qt::white;

            if (clockwise==1)
                (*pos)->clockwise=true;
            else
                (*pos)->clockwise=false;
        }
        if (increment)
            start();
    }
    update();
}

//squares and properties
void zeichenFeld::placeObject(void)
{
    int phase[4]={0, 0, 0, 0}; //line of movement
    bool clockwise[4]={true, true, true, true}; //direction
    int speed[4]={1,2,4,8}; //speed
    enum Qt::GlobalColor color[4]={Qt::red, Qt::green, Qt::blue, Qt::black}; //color
    int x[4]={25, 275, 1025, 775}; //x value
    int y[4]={25, 275, 25, 275}; //y value
    double angle[4]={0.0, 0.0, 0.0, 0.0}; //angle (necessary for circular movement)

    struct myDrawingObject *object;

    for (int rectNr=0; rectNr<4; rectNr++)
    {
        object=new myDrawingObject;
        object->phase=phase[rectNr];
        object->clockwise=clockwise[rectNr];
        object->speed=speed[rectNr];
        object->color=color[rectNr];
        object->x=object->startx=x[rectNr];
        object->y=object->starty=y[rectNr];
        object->angle=angle[rectNr];
        objects.push_back(object);
    }
    update();
}
