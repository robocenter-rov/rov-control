#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T22:59:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rov-control
TEMPLATE = app

LIBS += -lSDL2

SOURCES += main.cpp\
        mainwindow.cpp \
        messages.cpp

HEADERS  += mainwindow.h \
        messages.h

FORMS    += mainwindow.ui
