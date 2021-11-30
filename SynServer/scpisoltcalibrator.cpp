#include "scpisoltcalibrator.h"

ScpiSoltCalibrator::ScpiSoltCalibrator()
{
    getDeviceInfo();
}

QString ScpiSoltCalibrator::deviceInfo() const
{
    return _deviceInfo;
}

void ScpiSoltCalibrator::getDeviceInfo()
{
    QString newDeviceInfo = _session.deviceInfo();
    if (_deviceInfo != newDeviceInfo) {
        _deviceInfo = newDeviceInfo;
        emit ISoltCalibrator::deviceInfoChanged(_deviceInfo);
    }
}
