#ifndef SCPISOCKETSESSION_H
#define SCPISOCKETSESSION_H

#include <QObject>
#include <QTcpSocket>

class ScpiSocketSession : public QObject
{
    Q_OBJECT
public:
    ScpiSocketSession();
    ~ScpiSocketSession();

    QString deviceInfo() const;

signals:
    void connectedToHost();
    void disconnectedFromHost();

private:
    QString _host {"127.0.0.1"};
    quint16 _port {5025};
    QTcpSocket *_socket;
    uint _timeout {300};
};

#endif // SCPISOCKETSESSION_H
