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

void ScpiSession::getId()
{
    _socket->write("*IDN?\n");
    if (!_socket->waitForReadyRead(_timeout))
    {
        return;
    }
    setId(_socket->readLine());
}

QString ScpiSession::id() const
{
    return m_id;
}

void ScpiSession::setId(const QString &id)
{
    if (m_id != id)
    {
        m_id = id;
        emit idChanged(m_id);
    }
}
