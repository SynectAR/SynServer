#ifndef SCPISOLTCALIBRATOR_H
#define SCPISOLTCALIBRATOR_H

#include "isoltcalibrator.h"

#include "scpisocketsession.h"

#include <QVector>
#include <QMap>
#include <QString>

class ScpiSoltCalibrator : public ISoltCalibrator
{
public:
    ScpiSoltCalibrator();

    void apply() override;
    QString deviceInfo() const override;
    void measurePort(Measure measure, int port) override;
    void measureThru(int srcport, int rcvport) const override;
    int portCount() const override;
    PortStatus portStatus(int port) const override;
    void reset() override;

private:
    void getDeviceInfo();
    void getPortCount();

    void chooseCalibrationKit(int kit) const;
    void solt2Calibration(int port1, int port2) const;

private:
    ScpiSocketSession _session;

    QString _deviceInfo;
    int _portCount;

    QVector<Port> _ports;

    QMap<QString, Gender> _gender {
        { "M", Gender::MALE },
        { "F", Gender::FEMALE }
    };
    QMap<Measure, QString> _measureName {
        { Measure::OPEN, "OPEN" },
        { Measure::SHORT, "SHORT" },
        { Measure::LOAD, "LOAD" }
    };
};

#endif // SCPISOLTCALIBRATOR_H
