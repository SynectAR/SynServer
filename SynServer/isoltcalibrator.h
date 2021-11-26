#ifndef ISOLTCALIBRATOR_H
#define ISOLTCALIBRATOR_H

#include <QObject>

struct PortStatus
{
    enum class Gender
    {
        MALE,
        FEMALE
    };

    enum class Type
    {
        LOAD,
        LONG,
        SHORT
    };

    bool LOAD;
    bool LONG;
    bool SHORT;

    Gender gender;
};


class ISoltCalibrator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)
public:
    virtual ~ISoltCalibrator() = default;

    virtual void apply() const = 0;
    virtual QString deviceInfo() const = 0;
    virtual int portCount() const = 0;
    virtual PortStatus portStatus(int) const = 0;
    virtual void measurePort(int, PortStatus::Gender, PortStatus::Type) const = 0;
    virtual void measureThru() const = 0;
    virtual void reset() const = 0;

signals:
    void deviceInfoChanged(QString deviceInfo);
};


#endif // ISOLTCALIBRATOR_H
