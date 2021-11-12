#ifndef SCPISESSION_H
#define SCPISESSION_H

#include <QObject>
#include <QTcpSocket>

class ScpiSession : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
public:
    ScpiSession();
    ~ScpiSession();
    void getId();

    QString id() const;

public slots:
    void setId(const QString &);
signals:
    void connectedToHost();
    void idChanged(const QString &id);
private:
    QString _host{"127.0.0.1"};
    quint16 _port {5025};
    QTcpSocket* _socket;
    uint _timeout {300};

    QString m_id;
};

#endif // SCPISESSION_H
