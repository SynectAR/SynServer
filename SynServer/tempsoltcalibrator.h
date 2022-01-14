#ifndef TEMPSOLTCALIBRATOR_H
#define TEMPSOLTCALIBRATOR_H

#include "isoltcalibrator.h"

class TempSoltCalibrator : public ISoltCalibrator
{
public:
    TempSoltCalibrator();

    void apply(int channel) override;
    QString deviceInfo() const override;
    void measurePort(Measure measure, int channel, int port) override;
    void measureThru(int channel, int srcport, int rcvport) override;
    int portCount() const override;
    PortStatus portStatus(int channel, int port) const override;
    void reset(int channel) override;
    void soltCalibration(int channel, const QVector<int> &ports) const override;

private:
    PortStatus ports[2];
};

#endif // TEMPSOLTCALIBRATOR_H
