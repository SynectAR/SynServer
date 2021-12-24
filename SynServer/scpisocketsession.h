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
    double bandwidth() const;
    QString calibrationType() const;
    void clear() const;
    void chooseCalibrationKit(int kit) const;
    void chooseCalibrationSubclass(int subclass) const;
    int channelLayout() const;
    QString deviceInfo() const;
    int errorCode() const;
    QString format() const;
    double frequencyCenter() const;
    double frequncySpan() const;
    QString getSubclassGender(int subclass) const;
    bool isReady() const;
    bool isTriggerContinuous() const;
    double maxFrequency() const;
    double maxPower() const;
    double minFrequency() const;
    double minPower() const;
    QString measurementParameter(int trace) const;
    void measurePort(QString type, int port) const;
    void measureThru(int rcvport, int srcport) const;
    int number() const;
    int pointsCount() const;
    int portCount() const;
<<<<<<< HEAD
    QStringList readData() const;
    void reset() const;
    void selectActiveTrace() const;
    void selectTraceParameter(QString parameter) const;
    void setMinFrequency(qreal minFrequency) const;
    void setMaxFrequency(qreal maxFrequency) const;
    void setBandWidth(uint bandWidth) const;
    void setPointNumber(uint pointNumber) const;
    void setReadTraceFormat(QString format) const;
=======
    double power() const;
    double powerCenter() const;
    double powerSpan() const;
    void reset() const;
    bool rfOut() const;
    double scale() const;
>>>>>>> origin/master
    void solt2Calibration(int port1, int port2) const;
    QString sweepType() const;
    int traceCount() const;
    QString triggerScope() const;
    QString triggerSource() const;

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
    uint _timeout {500};
};

#endif // SCPISOCKETSESSION_H
