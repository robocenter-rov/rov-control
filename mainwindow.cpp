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
      _depthTimer(new QTimer(this)) // Temp timer. Look header
{
    _ui->setupUi(this);
    cameraInit();
    loadQSS();

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
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::Resize ) {
        _ui->mainView->fitInView(_mainCamera->getScene()->sceneRect(), Qt::KeepAspectRatio);
        return true;
    }
    return false;
}

void MainWindow::updateDepth()
{
    clearScene();
    QGraphicsScene *scene = _ui->mainView->scene();
    qreal h = scene->height()/15;
    qreal middle_y = _sceneHeight/2;
    qreal height = _sceneHeight;

    //qreal currentDepth = 63.0; // Temp code. Temp value

    qreal nearestUp = int(_currentDepth) - (int(_currentDepth) == _currentDepth),
          nearestDown = int(_currentDepth) + 1;
    qreal p = _currentDepth - int(_currentDepth), q = 1 - p;

    if (p == 0) p = 1;
    QString s;

    for (qreal i = middle_y + q*h; i < height; i += h){
        scene->addLine(1, i, 8, i);
        scene->addLine(1, i - h/2, 4, i - h/2);
        s.clear(); s.setNum(nearestDown++);
        scene->addText(s)->setPos(QPointF(20.0, i - 12));
    }

    for (qreal i = middle_y - p*h; i > 10; i -= h){
        scene->addLine(1, i, 8, i);
        scene->addLine(1, i + h/2, 4, i + h/2);
        s.clear(); s.setNum(nearestUp--);
        scene->addText(s)->setPos(QPointF(20.0, i - 12));
    }

    QVector<QPointF> points;
    points << QPointF(1, middle_y - 4) << QPointF(20, middle_y) << QPointF(1, middle_y + 4);
    QPolygonF pointer(points);
    scene->addPolygon(pointer, QPen(QColor(0, 0, 127)), QBrush(QColor(97, 143, 255)));
    s.clear(); s.setNum(_currentDepth); s += (_currentDepth - int(_currentDepth)) ? "" : ".0"; s += " cm";
    scene->addText(s, QFont("Times", 10, QFont::Bold))->setPos(QPointF(36.0, middle_y - 12));
    _currentDepth -= 0.1; // Temp code. For demonstration
}

void MainWindow::clearScene()
{
    QList<QGraphicsItem *> t = _ui->mainView->scene()->items();
    for (auto it = t.begin(); it != t.end(); it++) {
        _ui->mainView->scene()->removeItem(dynamic_cast<QGraphicsItem *>(*it));
    }
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
