#include "robocamera.h"

RoboCamera::RoboCamera()
{
    sceneInit();
}

RoboCamera::RoboCamera(QGraphicsView *gv, QObject *gv_parent, const QByteArray &deviceName = "")
{
    /* DO : use deviceName */

    sceneInit();

    _camera = new QCamera();
    _imageCapture = new QCameraImageCapture(_camera);
    _imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    _camera->setCaptureMode(QCamera::CaptureStillImage);
    _camera->setViewfinder(_videoWidget);
    _camera->start();

    gv->setScene(_scene);
    gv->viewport()->installEventFilter(gv_parent);
    gv->show();
}

RoboCamera::~RoboCamera()
{
    delete _scene;
    delete _videoWidget;
    delete _camera;
    delete _imageCapture;
    _scene = nullptr;
    _videoWidget = nullptr;
    _camera = nullptr;
    _imageCapture = nullptr;
}

QGraphicsScene *RoboCamera::getScene() const
{
    return this->_scene;
}

void RoboCamera::sceneInit()
{
    _scene = new QGraphicsScene();
    _videoWidget = new QVideoWidget();
    _scene->addWidget(_videoWidget);
}

void RoboCamera::imageCapture()
{
    _camera->searchAndLock();
    char buf[10];
    itoa(_imgId++, (char *)buf, 10);
    QString path(QCoreApplication::applicationDirPath());
    _imageCapture->capture(path);
    _lastSavedImg = _videoWidget->grab().toImage();
    _camera->unlock();
}

QImage RoboCamera::getLastSavedImage()
{
    return _lastSavedImg;
}