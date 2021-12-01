#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    void startListening();

public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();
    void sendMessage(QString) const;
    void sendPicture();

signals:
    void updateServerState(QString);
    void peerConnected(QString);
    void peerDisconnected();

private:
    QTcpServer *mTcpServer;
    QTcpSocket *mTcpSocket;
};

#endif // MYTCPSERVER_H
