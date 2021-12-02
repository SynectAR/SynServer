#include "scpisoltcalibrator.h"

ScpiSoltCalibrator::ScpiSoltCalibrator()
{
    getDeviceInfo();
    getPortCount();

    _ports.resize(_portCount);
    for (auto& port: _ports)
        port.gender = _gender[_session.getSubclassGender(1)];

    chooseCalibrationKit(1);
    solt2Calibration(1, 2);
}

void ScpiSoltCalibrator::apply()
{
    _session.apply();

    for (auto& port: _ports)
        for (auto& measure: port.measures)
            measure = false;
}

QString ScpiSoltCalibrator::deviceInfo() const
{
    return _deviceInfo;
}

void ScpiSoltCalibrator::measurePort(Measure measure, int port)
{
    if (port <= 0 || _portCount < port)
        return;
    _session.chooseCalibrationSubclass(1);

    _session.measurePort(_measureName[measure], port);
    _ports[port - 1].measures[measure] = true;
}

void ScpiSoltCalibrator::measureThru(int srcport, int rcvport) const
{
    if ((srcport <= 0 || _portCount < srcport)
       || (rcvport <= 0 || _portCount < rcvport)
       || (rcvport == srcport))
        return;

    _session.measureThru(srcport, rcvport);
}

int ScpiSoltCalibrator::portCount() const
{
    return _portCount;
}

PortStatus ScpiSoltCalibrator::portStatus(int port) const
{
    if (port <= 0 || _portCount < port)
        return {};

    PortStatus status;
    status.OPEN = _ports[port-1].measures[Measure::OPEN];
    status.SHORT = _ports[port-1].measures[Measure::SHORT];
    status.LOAD = _ports[port-1].measures[Measure::LOAD];
    status.gender = _ports[port-1].gender;

    return status;
}

void ScpiSoltCalibrator::reset()
{
    _session.reset();

    for (auto& port: _ports)
        for (auto& measure: port.measures)
            measure = false;
}

void ScpiSoltCalibrator::chooseCalibrationKit(int kit) const
{
    if (kit <= 0 || 64 < kit)
        return;
    _session.chooseCalibrationKit(kit);
}

void ScpiSoltCalibrator::getDeviceInfo()
{
    QString newDeviceInfo = _session.deviceInfo();
    if (_deviceInfo != newDeviceInfo) {
        _deviceInfo = newDeviceInfo;
        emit ISoltCalibrator::deviceInfoChanged(_deviceInfo);
    }
}

void ScpiSoltCalibrator::getPortCount()
{
    int newPortCount = _session.portCount();
    if (_portCount != newPortCount) {
        _portCount = newPortCount;
        emit ISoltCalibrator::portCountChanged(_portCount);
    }
}

void ScpiSoltCalibrator::solt2Calibration(int port1, int port2) const
{
    if ((port1 <= 0 || _portCount < port1)
       || (port2 <= 0 || _portCount < port2)
       || (port1 == port2))
        return;

    _session.solt2Calibration(port1, port2);
}
