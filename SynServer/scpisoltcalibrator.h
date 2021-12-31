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

    void apply(int channel) override;
    QString deviceInfo() const override;
    void measurePort(Measure measure, int channel, int port) override;
    void measureThru(int channel, int srcport, int rcvport) override;
    int portCount() const override;
    PortStatus portStatus(int channel, int port) const override;
    QVector<double> vnaData(int channel, int trace) const override;
    void reset(int channel) override;
    void soltCalibration(int channel, const QVector<int> &ports) const override;

private:
    void getDeviceInfo();
    void getPortCount();

    void chooseCalibrationKit(int kit) const;
    bool isChannelCorrect(int channel) const;
    bool isPortCorrect(int port) const;
    void prepareDevice() const;

    void clearStatus(PortStatus &port);

private:
    ScpiSocketSession _session;

    QString _deviceInfo;
    int _portCount;

    QVector<QVector<PortStatus>> _channelPorts;

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
