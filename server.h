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
public:
    explicit MyTcpServer(QObject *parent = 0);
    void startListening();

    QString deviceInfo() const;

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
private:
    QTcpServer *mTcpServer;
    QTcpSocket *mTcpSocket;

    ScpiSession session;

    QString m_deviceInfo;
};

#endif // MYTCPSERVER_H
