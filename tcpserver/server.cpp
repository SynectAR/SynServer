#include "server.h"
#include "mainwindow.h"
#include <QDebug>
#include <QCoreApplication>
#include <QImage>
#include <QPixmap>
#include <QBuffer>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
}

void MyTcpServer::startListening()
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::AnyIPv4, 8000)){
        qDebug() << "server is not started";
        emit updateServerState("server is not started");
    } else {
        qDebug() << "server is started " << mTcpServer->serverAddress().toString()
                 << mTcpServer->serverPort();
        emit updateServerState("server is started on ip: " + mTcpServer->serverAddress().toString());
    }
}

void MyTcpServer::sendPicture()
{
    QImage image(":/qrc/images/2.png");
    QByteArray bytes;
    int size = static_cast<int>(image.sizeInBytes());
    bytes.append(reinterpret_cast<char*>(&size), sizeof (size));
    bytes.append((char *)image.bits(),image.sizeInBytes());
    qDebug() << size << image.sizeInBytes() << bytes.size();
    mTcpSocket->write(bytes);
    qDebug() << bytes;
}

void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    emit peerConnected(mTcpSocket->peerAddress().toString());

    sendPicture();

    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    while(mTcpSocket->bytesAvailable()>0)
    {
        QByteArray array = mTcpSocket->readAll();
        mTcpSocket->write(array);
    }
}

void MyTcpServer::slotClientDisconnected()
{
    emit peerDisconnected();
    mTcpSocket->close();
}
