#include "server.h"

#include <QBuffer>
#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <QNetworkInterface>
#include <QPixmap>


MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {}

void MyTcpServer::startListening()
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    QString addressToListen;
    for (auto &address : QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost) {
            addressToListen = address.toString();
        }
    }

    if (!mTcpServer->listen(QHostAddress(addressToListen), 8000)) {
        qDebug() << "server is not started";
        emit updateServerState("server is not started");
    } else {
        qDebug() << "server is started " << mTcpServer->serverAddress().toString()
                 << mTcpServer->serverPort();
        emit updateServerState("server ip: " + mTcpServer->serverAddress().toString());
    }
}

void MyTcpServer::sendMessage(QString message) const
{
    mTcpSocket->write(message.toLocal8Bit());
}

void MyTcpServer::sendPicture()
{
    QImage image(":/qrc/images/2.png");
    QByteArray bytes;
    int size = static_cast<int>(image.sizeInBytes());
    bytes.append(reinterpret_cast<char *>(&size), sizeof(size));
    bytes.append((char *)image.bits(),image.sizeInBytes());
    qDebug() << size << image.sizeInBytes() << bytes.size();
    mTcpSocket->write(bytes);
    qDebug() << bytes;
}

void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    emit peerConnected(mTcpSocket->peerAddress().toString());

    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    while (mTcpSocket->bytesAvailable() > 0) {
        QByteArray array = mTcpSocket->readAll();
        mTcpSocket->write(array);
    }
}

void MyTcpServer::slotClientDisconnected()
{
    emit peerDisconnected();
    mTcpSocket->close();
}
