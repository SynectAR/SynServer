#include "scpisoltcalibrator.h"

ScpiSoltCalibrator::ScpiSoltCalibrator()
{
    getDeviceInfo();
}

void ScpiSoltCalibrator::apply() const
{
    // todo: implement
}

QString ScpiSoltCalibrator::deviceInfo() const
{
    return _deviceInfo;
}

int ScpiSoltCalibrator::portCount() const
{
    // todo: implement
    return 0;
}

PortStatus ScpiSoltCalibrator::portStatus(int) const
{
    // todo: implement
    return PortStatus{};
}

void ScpiSoltCalibrator::measurePort(int, PortStatus::Gender, PortStatus::Type) const
{
    // todo: implement
}

void ScpiSoltCalibrator::measureThru() const
{
    // todo: implement
}

void ScpiSoltCalibrator::reset() const
{
    // todo: implement
}

void ScpiSoltCalibrator::getDeviceInfo()
{
    QString newDeviceInfo = _session.deviceInfo();
    if (_deviceInfo != newDeviceInfo) {
        _deviceInfo = newDeviceInfo;
        emit ISoltCalibrator::deviceInfoChanged(_deviceInfo);
    }
}
