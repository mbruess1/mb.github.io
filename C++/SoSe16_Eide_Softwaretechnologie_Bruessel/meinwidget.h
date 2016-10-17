// Qt5 add:
#include <QWidget>

#include "zeichenfelder.h"

class meinWidget : public QWidget
{
    public:
        meinWidget(QWidget *parent = 0);

    private:
         Q_OBJECT // notwendig, da Slots enthalten sind
         zeichenFeld *meinZeichenFeld = new zeichenFeld;

    private slots:
        void start(void);
        void stop(void);
        void saveFile(void);
        void loadFile(void);
};
