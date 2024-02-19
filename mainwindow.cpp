#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(W, H);
    setWindowTitle("Zoo");

    QDateTime cd = QDateTime::currentDateTime();
    qsrand(cd.toTime_t());

    //animals = new Animal*[ANI_COUNT];

    for(int i = 0; i < ANI_COUNT; i++)
    {
        if(qrand() % 2 == 0)
            animals.append(new Predator(getRandomX(), getRandomY()));
            //animals[i] = new Predator(getRandomX(), getRandomY());
        else
            animals.append(new Vegan(getRandomX(), getRandomY()));
            //animals[i] = new Vegan(getRandomX(), getRandomY());

        animals[i]->rad_age = qrand() % ((77 + 1) - 5) + 5;
    }

    qtim = new QTimer();
    qtim->setInterval(100);
    connect(qtim, SIGNAL(timeout()), this, SLOT(newGen()));
    qtim->start();
}

MainWindow::~MainWindow()
{
    //delete animals;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    qpaint = new QPainter();
    qpaint->begin(this);

    for(int i = 0; i < ANI_COUNT; i++)
    {
        animals[i]->Tick(qpaint);
    }

    for(int i = 0; i < log.length(); i++)
    {
        qpaint->drawText(10, 20 + i * 12, log[i]);
    }

    qpaint->end();
}

int MainWindow::getRandomX()
{
    return qrand() % ((W + 1) - 0) + 0;
}

int MainWindow::getRandomY()
{
    return qrand() % ((H + 1) - 0) + 0;
}

void MainWindow::toLog(QString info)
{
    if (log.size() == 5)
        log.removeFirst();
     log.append(info);
}

void MainWindow::newGen()
{
    ageControl();
    huntControl();
    repaint();
    qtim->start();
}

void MainWindow::ageControl()
{
    for(int i = 0; i < ANI_COUNT; i++)
        if (animals[i]->rad_age > 77)
        {
            toLog(animals[i]->color == QColor(255, 0, 0) ? "Predator died" : "Vegan died");
            animals[i] = bornNew();
            death->play();
        }
}

void MainWindow::huntControl()
{
    for(int i = 0; i < ANI_COUNT; i++)
    {
        for(int j = 0; j < ANI_COUNT; j++)
        {
            if (i != j)
            {
                double dist = qSqrt(qPow(animals[i]->x - animals[j]->x, 2) + qPow(animals[i]->y - animals[j]->y, 2));
                double dist_max = animals[i]->rad_age + animals[j]->rad_age;
                if (dist < dist_max)
                {
                    // оба хищника, один меньше
                    if (animals[i]->rad_age > animals[j]->rad_age
                            && animals[i]->color == QColor(255,0,0)
                            && animals[j]->color == QColor(255,0,0))
                    {
                        bear->play();
                        toLog("Predator killed, age: " + QString::number(animals[j]->rad_age));
                        delete animals[j];
                        animals[j] = bornNew();
                    }
                    // хищник и веган
                    if (animals[i]->color == QColor(255,0,0)
                            && animals[i]->color != animals[j]->color)
                    {
                        chicken->play();
                        toLog("Vegan killed, age: " + QString::number(animals[j]->rad_age));
                        delete animals[j];
                        animals[j] = bornNew();

                    }
                }
            }
        }
    }
}

Animal* MainWindow::bornNew()
{
    if(qrand() % 2 == 0)
        return new Predator(getRandomX(), getRandomY());
    else
        return new Vegan(getRandomX(), getRandomY());
}
