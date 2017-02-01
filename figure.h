#ifndef FIGURE_H
#define FIGURE_H

#include "graphicsscene.h"

class Figure
{
public:
    Figure();
    ~Figure(){}
    void virtual draw(GraphicsScene *scene){}
protected:
    QPen _pen;
};

class LineFigure : public Figure
{
public:
    LineFigure(QPointF p1, QPointF p2);
    ~LineFigure(){}
    void draw(GraphicsScene *scene) override;
private:
    QPointF _p1;
    QPointF _p2;
};

class RectFigure : public Figure
{
public:
    RectFigure(QPointF p1, QPointF p2);
    ~RectFigure(){}
    void draw(GraphicsScene *scene) override;
private:
    QPointF _p1;
    QPointF _p2;
};

extern void calcPoints(QPointF &p1, QPointF &p2);
#endif // FIGURE_H
