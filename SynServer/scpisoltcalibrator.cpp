#include "scpisoltcalibrator.h"

ScpiSoltCalibrator::ScpiSoltCalibrator()
{
    getDeviceInfo();
    getPortCount();

    _ports.resize(_portCount);
    for (auto& port: _ports) {
        port.gender = _gender[_session.getSubclassGender(1)];
        port.THRU.resize(_portCount);
    }

    chooseCalibrationKit(1);
}

void ScpiSoltCalibrator::apply()
{
    _session.apply();

    for (auto &port: _ports)
        clearStatus(port);
}

QString ScpiSoltCalibrator::deviceInfo() const
{
    return _deviceInfo;
}

void ScpiSoltCalibrator::measurePort(Measure measure, int port)
{
    if (port <= 0 || _portCount < port)
        return;

    _session.clear();
    _session.chooseCalibrationSubclass(1);
    _session.measurePort(_measureName[measure], port);

    if (_session.errorCode() != 0)
        return;

    switch (measure) {
    case Measure::OPEN:
        _ports[port - 1].OPEN = true;
        break;
    case Measure::SHORT:
        _ports[port - 1].SHORT = true;
        break;
    case Measure::LOAD:
        _ports[port -1].LOAD = true;
        break;
    }
}

void ScpiSoltCalibrator::measureThru(int srcport, int rcvport)
{
    if ((srcport <= 0 || _portCount < srcport)
       || (rcvport <= 0 || _portCount < rcvport)
       || (rcvport == srcport))
        return;

    _ports[srcport - 1].THRU[rcvport - 1] = true;
    _ports[rcvport - 1].THRU[srcport - 1] = true;


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

    return _ports[port - 1];
}

QVector<double> ScpiSoltCalibrator::vnaData() const
{
    QVector<double> vnaData;
    auto data = _session.readData();

    vnaData.reserve(data.size() / 2);

    for (size_t i = 0; i < data.size(); i += 2)
        vnaData.push_back(data[i].toDouble());

    return vnaData;
}

void ScpiSoltCalibrator::reset()
{
    _session.reset();

    for (auto &port: _ports)
        clearStatus(port);
}

void ScpiSoltCalibrator::solt2Calibration(int port1, int port2) const
{
    if ((port1 <= 0 || _portCount < port1)
       || (port2 <= 0 || _portCount < port2)
       || (port1 == port2))
        return;

    _session.solt2Calibration(port1, port2);
}

void ScpiSoltCalibrator::chooseCalibrationKit(int kit) const
{
    if (kit <= 0 || 64 < kit)
        return;
    _session.chooseCalibrationKit(kit);
}

void ScpiSoltCalibrator::prepareDevice() const
{
    _session.selectTraceParameter("S11");
    _session.selectActiveTrace();
    _session.setReadTraceFormat("MLOG");
    _session.setMinFrequency(0);
    _session.setMaxFrequency(9);
    _session.setBandWidth(10'000);
    _session.setPointNumber(201);
}

void ScpiSoltCalibrator::clearStatus(PortStatus &port)
{
    port.OPEN = false;
    port.SHORT = false;
    port.LOAD = false;
    port.THRU.fill(false);
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
