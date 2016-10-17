#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "meinWidget.h"

meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{
    //Button: Ende
    QPushButton *quit = new QPushButton(tr("Ende"));
    quit->setFont(QFont("Times", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    //Button: Start
    QPushButton *startButton = new QPushButton(tr("Start"));
    startButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));

    //Button: Stop
    QPushButton *stopButton = new QPushButton(tr("Stop"));
    stopButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));

    //Button: Speichern
    QPushButton *saver = new QPushButton(tr("Speichern"));
    saver->setFont(QFont("Times", 18, QFont::Bold));
    connect(saver, SIGNAL(clicked()), this, SLOT(saveFile()));

    //Button: Laden
    QPushButton *loader = new QPushButton(tr("Laden"));
    loader->setFont(QFont("Times", 18, QFont::Bold));
    connect(loader, SIGNAL(clicked()), this, SLOT(loadFile()));

    //Zeichenfeld
    meinZeichenFeld->setFixedSize(1525,850);

    //Layout
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(quit, 0, 0);
    gridLayout->addWidget(startButton, 1, 0);
    gridLayout->addWidget(stopButton, 2, 0);
    gridLayout->addWidget(saver, 3, 0);
    gridLayout->addWidget(loader, 4, 0);
    gridLayout->addWidget(meinZeichenFeld, 0, 1, 5, 1);
    setLayout(gridLayout);
}

//Functions for buttons
void meinWidget::start(void)
{
    meinZeichenFeld->start();
}

void meinWidget::stop(void)
{
    meinZeichenFeld->stop();
}

void meinWidget::saveFile(void)
{
    meinZeichenFeld->savestop(); //freeze movement to save
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this, tr("Speichern unter"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            QMessageBox::warning(this, tr("Dateifehler"), tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);

        meinZeichenFeld->serialize(file);
        file.close();
    }
    meinZeichenFeld->savestart(); //resume
}

void meinWidget::loadFile(void)
{
    meinZeichenFeld->savestop(); //freeze movement to load
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this, tr("Öffnen"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            QMessageBox::warning(this, tr("Dateifehler"), tr("Folgende Datei kann nicht geöffnet werden: ") + fileName,QMessageBox::Ok);

        meinZeichenFeld->deserialize(file);
        file.close();
    }
    else
        meinZeichenFeld->savestart(); //resume
}

