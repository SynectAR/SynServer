#ifndef ISOLTCALIBRATOR_H
#define ISOLTCALIBRATOR_H

#include <QObject>


class ISoltCalibrator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)
public:
    virtual ~ISoltCalibrator() = default;

    virtual QString deviceInfo() const = 0;

signals:
    void deviceInfoChanged(QString deviceInfo);
};

#endif // ISOLTCALIBRATOR_H
