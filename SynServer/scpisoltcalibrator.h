#ifndef SCPISOLTCALIBRATOR_H
#define SCPISOLTCALIBRATOR_H

#include "isoltcalibrator.h"

#include "scpisocketsession.h"

class ScpiSoltCalibrator : public ISoltCalibrator
{
public:
    ScpiSoltCalibrator();

    QString deviceInfo() const override;

private:
    void getDeviceInfo();

private:
    ScpiSocketSession _session;
    QString _deviceInfo;
};

#endif // SCPISOLTCALIBRATOR_H
