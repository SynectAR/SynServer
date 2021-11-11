#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyTcpServer *server = new MyTcpServer;
    connect(server, SIGNAL(peerDisconnected()), this, SLOT(setDisconnected()));
    connect(server, SIGNAL(peerConnected(QString)), this, SLOT(setConnected(QString)));
    connect(server, SIGNAL(updateServerIp(QString)), this, SLOT(showIp(QString)));
    server->startListening();
}

void MainWindow::showIp(QString ip)
{
    qDebug() << ip;
    ui->ip_label->setText("server ip: " + ip);
}

void MainWindow::setConnected(QString peerIp)
{
    ui->peer_label->setText("Connected: " + peerIp);
}

void MainWindow::setDisconnected()
{
    ui->peer_label->setText("Disconnected");
}

MainWindow::~MainWindow()
{
    delete ui;
}
