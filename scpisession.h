#ifndef SCPISESSION_H
#define SCPISESSION_H

#include <QObject>
#include <QTcpSocket>

class ScpiSession : public QObject
{
    Q_OBJECT
public:
    ScpiSession();
    ~ScpiSession();

    void getDeviceInfo();
    QString deviceInfo() const;
signals:
    void connectedToHost();
private:
    QString _host {"127.0.0.1"};
    quint16 _port {5025};
    QTcpSocket *_socket;
    uint _timeout {300};

    QString _deviceInfo;
};

#endif // SCPISESSION_H
