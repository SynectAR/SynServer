#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include "scpisession.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyTcpServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)
    Q_PROPERTY(QString ip READ ip NOTIFY ipChanged)
public:
    explicit MyTcpServer(QObject *parent = 0);
    void startListening();

    QString deviceInfo() const;
    QString ip() const;

public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();
    void sendDeviceInfo();
    void sendPicture();

signals:
    void updateServerState(QString);
    void peerConnected(QString);
    void peerDisconnected();

    void deviceInfoChanged(QString deviceInfo);
    void ipChanged(QString ip);
private:
    QTcpServer *mTcpServer;
    QTcpSocket *mTcpSocket;

    ScpiSession session;

    QString m_deviceInfo;
    QString m_ip;
};

#endif // MYTCPSERVER_H
