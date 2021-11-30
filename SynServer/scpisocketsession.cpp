#include "scpisocketsession.h"


ScpiSocketSession::ScpiSocketSession()
    : _socket(new QTcpSocket(this))
{
    _socket->connectToHost(_host, _port);

    connect(_socket, &QAbstractSocket::stateChanged, this,
            [this](QAbstractSocket::SocketState s) {
        if (s == QTcpSocket::ConnectedState) {
            emit connectedToHost();
            qDebug() << "ScpiSocketSession::ScpiSocketSession()";
        }
    });
}

ScpiSocketSession::~ScpiSocketSession()
{
    _socket->disconnectFromHost();
}

QString ScpiSocketSession::deviceInfo() const
{
    _socket->write("*IDN?\n");
    if (!_socket->waitForReadyRead(_timeout)) {
        return "";
    }
    QString deviceInfo = _socket->readLine();
    qDebug() << "ScpiSocketSession::getDeviceInfo()" << deviceInfo;
    return deviceInfo;
}
