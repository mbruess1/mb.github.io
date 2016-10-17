using namespace std;
#include <QWidget>
#include <QtGui>
#include <QMessageBox>
#include <QFile>
#include <vector>
#include <String>

class zeichenFeld : public QWidget
{
    public:
        zeichenFeld(QWidget *parent = 0);
        ~zeichenFeld();

        void start(void) { timer->start(10); increment=1; }; //start(n) => increase n to slow the movement down
        void stop(void) { timer->stop(); increment=0; };
        void savestop(void) { timer->stop();}; //freezes squares at the press of the button Speichern/Laden to register exact position
        void savestart(void) {if (increment) start();}; //evaluates whether movement from before the press of the button Speichern is to be continued

        void serialize(QFile &file);
        void deserialize(QFile &file);

        void placeObject(void);

        bool rectangleCollision(const struct myDrawingObject *position1, float width1, float height1,
                                const struct myDrawingObject *position2, float width2, float height2);
        bool rectangleApproximation(const struct myDrawingObject *position1, float width1, float height1,
                                const struct myDrawingObject *position2, float width2, float height2);

    private:
        vector<struct myDrawingObject *> objects;
        QTimer *timer;
        int increment;

    protected:
        void paintEvent(QPaintEvent *event);
};

struct myDrawingObject
{
    int x, startx;
    int y, starty;
    int phase;
    bool clockwise;
    int speed;
    double angle;
    enum Qt::GlobalColor color, color2; //http://doc.qt.io/qt-5/qt.html#GlobalColor-enum
};
