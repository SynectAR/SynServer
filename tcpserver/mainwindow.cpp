#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyTcpServer *server = new MyTcpServer(this);
    connect(server, &MyTcpServer::peerDisconnected, this, &MainWindow::setDisconnected);
    connect(server, &MyTcpServer::peerConnected, this, &MainWindow::setConnected);
    connect(server, &MyTcpServer::updateServerState, this, &MainWindow::showServerState);
    server->startListening();
}

void MainWindow::showServerState(QString state)
{
    qDebug() << state;
    ui->ip_label->setText(state);
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
