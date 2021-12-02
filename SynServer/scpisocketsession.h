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

    void apply() const;
    void chooseCalibrationKit(int kit) const;
    void chooseCalibrationSubclass(int subclass) const;
    QString deviceInfo() const;
    QString getSubclassGender(int subclass) const;
    void measurePort(QString type, int port) const;
    void measureThru(int rcvport, int srcport) const;
    int portCount() const;
    void reset() const;
    void solt2Calibration(int port1, int port2) const;


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
    uint _timeout {300};
};

#endif // SCPISOCKETSESSION_H
