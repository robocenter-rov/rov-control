#ifndef FIGURE_H
#define FIGURE_H

#include "graphicsscene.h"
#include <string>

#include <QList>

using namespace std;

class Figure
{
public:
    Figure();
    ~Figure(){}
    void virtual draw(QGraphicsScene *scene) {}
    void virtual drawArea(QGraphicsScene *scene) {}
    void virtual drawResizePoints(QGraphicsScene *scene) {}
    bool virtual inArea(QPointF p) { return true; }
    int virtual inResizePointArea(QPointF p) { return false; }
    void virtual resetPoints(QPointF deltaPoint) {}
    void virtual resizePoint(int idx, QPointF point) {}
    void virtual calcArea() {}
    void virtual calcResizePoints() {}
    void virtual sortPoints() {}
    QString virtual getInfo() { return ""; }
protected:
    QPen _pen;
    QList<QPolygonF> _resizePoints;
    const double _offset = 3;
};

class LineFigure : public Figure
{
public:
    LineFigure(QPointF p1, QPointF p2);
    ~LineFigure(){}
    void draw(QGraphicsScene *scene) override;
    void drawArea(QGraphicsScene *scene) override;
    void drawResizePoints(QGraphicsScene *scene) override;
    bool inArea(QPointF p) override;
    int inResizePointArea(QPointF p) override;
    void resetPoints(QPointF deltaPoint) override;
    void resizePoint(int idx, QPointF point) override;
    void calcArea() override;
    void calcResizePoints() override;
    void sortPoints() override;
    QString getInfo() override;
    int length();
    QPointF rotatedEndPoint2();
private:
    QPointF _p1;
    QPointF _p2;
    QPolygonF _area;
    double _angle;
};

#endif // FIGURE_H
