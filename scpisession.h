#ifndef SCPISESSION_H
#define SCPISESSION_H

#include <QObject>
#include <QTcpSocket>

class ScpiSession : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)
public:
    ScpiSession();
    ~ScpiSession();
    void getDeviceInfo();

    QString deviceInfo() const;

public slots:

signals:
    void connectedToHost();
    void deviceInfoChanged(const QString &info);
private:
    QString _host{"127.0.0.1"};
    quint16 _port {5025};
    QTcpSocket *_socket;
    uint _timeout {300};

    QString m_deviceInfo;
};

#endif // SCPISESSION_H
