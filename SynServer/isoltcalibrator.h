#ifndef ISOLTCALIBRATOR_H
#define ISOLTCALIBRATOR_H

#include <QMap>
#include <QObject>
#include <QVector>

enum class Gender
{
    male,
    female
};

enum class Measure
{
    OPEN,
    SHORT,
    LOAD
};

struct PortStatus
{
    bool OPEN {false};
    bool SHORT {false};
    bool LOAD {false};
    QVector<bool> THRU;

    Gender gender;
};

class ISoltCalibrator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)
    Q_PROPERTY(int portCount READ portCount NOTIFY portCountChanged)
public:
    virtual ~ISoltCalibrator() = default;

    virtual void apply(int channel) = 0;
    virtual QString deviceInfo() const = 0;
    virtual void measurePort(Measure measure, int channel, int port) = 0;
    virtual void measureThru(int channel, int srcport, int rcvport) = 0;
    virtual int portCount() const = 0;
    virtual PortStatus portStatus(int channel, int port) const = 0;
    virtual QVector<double> vnaData(int channel, int trace) const = 0;
    virtual void reset(int channel) = 0;
    virtual void solt2Calibration(int channel, int port1, int port2) const = 0;

signals:
    void deviceInfoChanged(QString deviceInfo);
    void portCountChanged(int portCount);
};


#endif // ISOLTCALIBRATOR_H
