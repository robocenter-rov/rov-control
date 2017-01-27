#ifndef CALCWINDOW_H
#define CALCWINDOW_H

#include <QMainWindow>
#include "robocamera.h"
#include <QGraphicsPixmapItem>

namespace Ui {
class CalcWindow;
}

class CalcWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalcWindow(QWidget *parent = 0);
    ~CalcWindow();

private slots:
    void onMakeScreenButtonClicked();

private:
    void loadQSS();
    bool eventFilter(QObject *, QEvent *event);

    Ui::CalcWindow *_ui;
    RoboCamera *_mainCamera;
    QGraphicsScene *_screenScene;
    QGraphicsPixmapItem _screen;
};

#endif // CALCWINDOW_H
