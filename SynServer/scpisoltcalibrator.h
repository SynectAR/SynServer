#ifndef SCPISOLTCALIBRATOR_H
#define SCPISOLTCALIBRATOR_H

#include "isoltcalibrator.h"

#include "scpisocketsession.h"

class ScpiSoltCalibrator : public ISoltCalibrator
{
public:
    ScpiSoltCalibrator();

    void apply() const override;
    QString deviceInfo() const override;
    int portCount() const override;
    PortStatus portStatus(int) const override;
    void measurePort(int, PortStatus::Gender, PortStatus::Type) const override;
    void measureThru() const override;
    void reset() const override;

private:
    void getDeviceInfo();

private:
    ScpiSocketSession _session;
    QString _deviceInfo;
};

#endif // SCPISOLTCALIBRATOR_H
