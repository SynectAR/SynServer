#ifndef ISOLTCALIBRATOR_H
#define ISOLTCALIBRATOR_H

#include <QMap>
#include <QObject>

enum class Gender
{
    MALE,
    FEMALE
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

    Gender gender;
};

class ISoltCalibrator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)
    Q_PROPERTY(QString portCount READ portCount NOTIFY portCountChanged)
public:
    virtual ~ISoltCalibrator() = default;

    virtual void apply() = 0;
    virtual QString deviceInfo() const = 0;
    virtual void measurePort(Measure measure, int port) = 0;
    virtual void measureThru(int srcport, int rcvport) const = 0;
    virtual int portCount() const = 0;
    virtual PortStatus portStatus(int port) const = 0;
    virtual void reset() = 0;

signals:
    void deviceInfoChanged(QString deviceInfo);
    void portCountChanged(int portCount);
};


#endif // ISOLTCALIBRATOR_H
