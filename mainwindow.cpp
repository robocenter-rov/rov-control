#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

#define IP_ADDR "127.0.0.1"
#define PORT 8000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress(IP_ADDR), PORT);
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SendMessage() {
    QByteArray Data;
    Data.append("Hello, robot!");
    socket->writeDatagram(Data, QHostAddress(IP_ADDR), PORT);
}

void MainWindow::ReadyRead(){
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}

void MainWindow::on_sendButton_clicked() {
    SendMessage();
}
