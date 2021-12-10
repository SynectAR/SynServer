#ifndef TEMPSOLTCALIBRATOR_H
#define TEMPSOLTCALIBRATOR_H

#include "isoltcalibrator.h"

class TempSoltCalibrator : public ISoltCalibrator
{
public:
    TempSoltCalibrator();

    void apply() override;
    QString deviceInfo() const override;
    void measurePort(Measure measure, int port) override;
    void measureThru(int srcport, int rcvport) const override;
    int portCount() const override;
    PortStatus portStatus(int port) const override;
    void reset() override;

private:
    PortStatus ports[2];
};

#endif // TEMPSOLTCALIBRATOR_H
