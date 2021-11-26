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

    bool apply() const;
    bool chooseCalibrationStandard() const;
    bool calibrate() const;
    QString deviceInfo() const;
    int portCount() const;
    QString measurePort(int port, QString type) const;
    QString measureThru() const;
    QString portStatus() const;
    bool reset() const;


signals:
    void connectedToHost();
    void disconnectedFromHost();

private:
    void runCommand(QString command) const;
    QString runQuery(QString query) const;

private:
    QString _host {"127.0.0.1"};
    quint16 _port {5025};
    QTcpSocket *_socket;
    uint _timeout {1000};
};

#endif // SCPISOCKETSESSION_H
