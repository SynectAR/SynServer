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
        emit updateServerIp("server is not started");
    } else {
        qDebug() << "server is started " << mTcpServer->serverAddress().toString()
                 << mTcpServer->serverPort();
        emit updateServerIp(mTcpServer->serverAddress().toString());
    }
}

void MyTcpServer::sendPicture()
{
    QImage image("C:/2.png");
    QByteArray bytes;
//    qDebug() << image.sizeInBytes() << image.size();
    int size = static_cast<int>(image.sizeInBytes());
    bytes.append(reinterpret_cast<char*>(&size), sizeof (size));
    bytes.append((char *)image.bits(),image.sizeInBytes());

//    bytes.append("\n");
    qDebug() << size << image.sizeInBytes() << bytes.size();
    mTcpSocket->write(bytes);
    qDebug() << bytes;
}

void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    emit peerConnected(mTcpSocket->peerAddress().toString());
    emit updateServerIp(mTcpServer->serverAddress().toString());

    sendPicture();

    //mTcpSocket->write("Hello, World!!!\r\n");
    //sendPicture();
    //sendPicture();
//    QString tStr = "Hello World!";
//    QByteArray testStr;
//    qDebug() << tStr.length();
//    QString s = (QString)tStr.length();
//    testStr.append(s.toUtf8());
//    testStr.append(tStr.toUtf8());

//    qDebug() << testStr << " " << testStr.size();
//    mTcpSocket->write(testStr);



    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    connect(mTcpSocket, &QTcpSocket::destroyed, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    while(mTcpSocket->bytesAvailable()>0)
    {
        QByteArray array = mTcpSocket->readAll();
        qDebug() << "array +++" << array;
        //qDebug() << array;
        //if((QString)array == "p") {
            //sendPicture();
            //qDebug() << array;
        //}
        //mTcpSocket->write(array);
    }
}

void MyTcpServer::slotClientDisconnected()
{
    emit peerDisconnected();
    mTcpSocket->close();
}
