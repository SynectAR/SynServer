#include "scpisession.h"


ScpiSession::ScpiSession()
{
    _socket = new QTcpSocket(this);
    _socket->connectToHost(_host, _port);

    connect(_socket, &QAbstractSocket::stateChanged, this,
            [this](QAbstractSocket::SocketState s) {
        if (s == QTcpSocket::ConnectedState)
        {
            emit connectedToHost();
        }
    });
}

ScpiSession::~ScpiSession()
{
    _socket->disconnectFromHost();
}

void ScpiSession::getDeviceInfo()
{
    _socket->write("*IDN?\n");
    if (!_socket->waitForReadyRead(_timeout))
    {
        return;
    }
    setDeviceInfo(_socket->readLine());
}

QString ScpiSession::deviceInfo() const
{
    return m_deviceInfo;
}
