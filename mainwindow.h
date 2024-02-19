#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QVector>
#include <QDateTime>
#include <QtCore>
#include <QSound>
#include <QDebug>
#include "globalconst.h"
#include "animal.h"
#include "predator.h"
#include "vegan.h"
#include <phonon/phonon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Phonon::MediaObject *death = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("/home/sergiano/qt/death.wav"));
    Phonon::MediaObject *chicken = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("/home/sergiano/qt/chicken.wav"));
    Phonon::MediaObject *bear = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("/home/sergiano/qt/bear.wav"));

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    QPainter *qpaint;
    QTimer *qtim;
    //Animal **animals;
    QVector<Animal*> animals;
    QList<QString> log;

    int getRandomX();
    int getRandomY();
    void toLog(QString info);
    void ageControl();
    void huntControl();
    Animal* bornNew();

private slots:
    void newGen();

};

#endif // MAINWINDOW_H
