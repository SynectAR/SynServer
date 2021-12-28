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
    double bandwidth(int channel) const;
    QString calibrationType(int channel) const;
    void clear() const;
    void chooseCalibrationKit(int kit) const;
    void chooseCalibrationSubclass(int subclass) const;
    int channelLayout() const;
    QString deviceInfo() const;
    int errorCode() const;
    QString format() const;
    double frequencyCenter(int channel) const;
    double frequncySpan(int channel) const;
    QString getSubclassGender(int subclass) const;
    bool isReady() const;
    bool isTriggerContinuous() const;
    double maxFrequency(int channel) const;
    double maxPower(int channel) const;
    double minFrequency(int channel) const;
    double minPower(int channel) const;
    QString measurementParameter(int channel, int trace) const;
    void measurePort(QString type, int port) const;
    void measureThru(int rcvport, int srcport) const;
    int number() const;
    int pointsCount(int channel) const;
    int portCount() const;
    double power(int channel) const;
    double powerCenter(int channel) const;
    double powerSpan(int channel) const;
    QStringList readData() const;
    void reset() const;
    bool rfOut() const;
    double scale() const;
    void selectActiveTrace() const;
    void selectTraceParameter(QString parameter) const;
    void setMinFrequency(qreal minFrequency) const;
    void setMaxFrequency(qreal maxFrequency) const;
    void setBandWidth(uint bandWidth) const;
    void setPointNumber(uint pointNumber) const;
    void setReadTraceFormat(QString format) const;
    void solt2Calibration(int port1, int port2) const;
    QString sweepType(int channel) const;
    int traceCount(int channel) const;
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
