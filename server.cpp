#include "server.h"

#include <QBuffer>
#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <QPixmap>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {
    qDebug() << "device info: " << session.deviceInfo();
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
        session.getDeviceInfo();
        m_deviceInfo = session.deviceInfo();
    }
}

QString MyTcpServer::deviceInfo() const
{
    return m_deviceInfo;
}

void MyTcpServer::sendDeviceInfo()
{
    mTcpSocket->write(m_deviceInfo.toLocal8Bit());
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

    sendDeviceInfo();

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
