#include "mainwindow.h"
#include <iostream>

void MainWindow::loadQSS()
{
    QFile styleF("../remote-control/qss/appstyles.css");
    if (!styleF.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Warning: application styles not found";
    }
    this->setStyleSheet(styleF.readAll());
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow),
      _communicator(new Communicator()),
      _taskTimer(new QTimer(this)),
      _depthTimer(new QTimer(this)) // Temp timer. Look header
{
    _ui->setupUi(this);
    cameraInit();
    loadQSS();
    connect(_ui->startButton, SIGNAL(clicked(bool)), this, SLOT(onStartButtonClick(bool)));
    connect(_taskTimer, SIGNAL(timeout()), this, SLOT(onTaskTimeout()));

    // Temp code begin
    _currentDepth = 50.1;
    _sceneHeight = _ui->mainView->scene()->height();
    _sceneWidth = _ui->mainView->scene()->width();
    // Temp code end

    connect(_depthTimer, SIGNAL(timeout()), this, SLOT(updateDepth()));
    _depthTimer->setInterval(100);
    _depthTimer->start();

}

MainWindow::~MainWindow()
{
    delete _ui;
    delete _communicator;
}

void MainWindow::cameraInit()
{
    _mainCamera = new RoboCamera(_ui->mainView, this);
    _extraCamera = new RoboCamera(_ui->extraView, this, nullptr, 1);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::Resize ) {
        _ui->mainView->fitInView(_mainCamera->getScene()->sceneRect(), Qt::KeepAspectRatioByExpanding);
        _ui->extraView->fitInView(_extraCamera->getScene()->sceneRect(), Qt::KeepAspectRatioByExpanding);
        return true;
    }
    return false;
}

void MainWindow::updateDepth()
{
    _mainCamera->getVideoWidget()->setCurrentDepth(_currentDepth);
    _currentDepth += 0.1;
}

void MainWindow::showMessage(QString msg, QColor msgColor)
{
    updateDepth();
    QGraphicsScene *scene = _ui->mainView->scene();
    scene->addRect(0, 0, scene->width(), 24, QPen(msgColor), QBrush(msgColor));

    QGraphicsTextItem *text = scene->addText(msg, QFont("Times", 10));
    text->setPos(QPointF(scene->width()/2 - 24, 0));
    text->setDefaultTextColor(QColor(255, 255, 255));
}

void MainWindow::onStartButtonClick(bool)
{
    _taskTimer->stop();
    _ui->minutesLCDNumber->display(15);
    _ui->secondsLCDNumber->display(0);
    _taskTimer->start(1000);
}

void MainWindow::onTaskTimeout()
{
    double min = _ui->minutesLCDNumber->value(), sec = _ui->secondsLCDNumber->value();

    if (sec == 0) {
        sec = 59;
        min -= 1;
    } else {
        sec -= 1;
    }

    if (min == 0.0 && sec == 0.0) {
        _taskTimer->stop();
    }

    _ui->minutesLCDNumber->display(min);
    _ui->secondsLCDNumber->display(sec);
}
