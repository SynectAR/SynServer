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
    void measureThru(int srcport, int rcvport) override;
    int portCount() const override;
    PortStatus portStatus(int port) const override;
    void reset() override;
    void solt2Calibration(int port1, int port2) const override;

private:
    void getDeviceInfo();
    void getPortCount();

    void chooseCalibrationKit(int kit) const;

    void clearStatus(PortStatus& port);

private:
    ScpiSocketSession _session;

    QString _deviceInfo;
    int _portCount;

    QVector<PortStatus> _ports;

    QMap<QString, Gender> _gender {
        { "M", Gender::male },
        { "F", Gender::female }
    };
    QMap<Measure, QString> _measureName {
        { Measure::OPEN, "OPEN" },
        { Measure::SHORT, "SHORT" },
        { Measure::LOAD, "LOAD" }
    };
};

#endif // SCPISOLTCALIBRATOR_H
