#include "scpisoltcalibrator.h"

ScpiSoltCalibrator::ScpiSoltCalibrator()
{
    getDeviceInfo();
    getPortCount();

    _channelPorts.resize(16);
    for (auto &ports: _channelPorts) {
        ports.resize(_portCount);
        for (auto &port: ports) {
            port.gender = _gender[_session.getSubclassGender(1)];
            port.THRU.resize(_portCount);
        }
    }

    chooseCalibrationKit(1);
}

void ScpiSoltCalibrator::apply(int channel)
{
    _session.apply(channel);

    for (auto &ports: _channelPorts)
        for (auto &port: ports)
            clearStatus(port);
}

QString ScpiSoltCalibrator::deviceInfo() const
{
    return _deviceInfo;
}

void ScpiSoltCalibrator::measurePort(Measure measure, int channel, int port)
{
    if (checkPort(port))
        return;

    _session.clear();
    _session.chooseCalibrationSubclass(channel, 1);
    _session.measurePort(_measureName[measure], channel, port);

    if (_session.errorCode() != 0)
        return;

    switch (measure) {
    case Measure::OPEN:
        _channelPorts[channel][port - 1].OPEN = true;
        break;
    case Measure::SHORT:
        _channelPorts[channel][port - 1].SHORT = true;
        break;
    case Measure::LOAD:
        _channelPorts[channel][port -1].LOAD = true;
        break;
    }
}

void ScpiSoltCalibrator::measureThru(int channel, int srcport, int rcvport)
{
    if (checkPort(srcport)
       || checkPort(rcvport)
       || (rcvport == srcport))
        return;

    _channelPorts[channel][srcport - 1].THRU[rcvport - 1] = true;
    _channelPorts[channel][rcvport - 1].THRU[srcport - 1] = true;


    _session.measureThru(channel, srcport, rcvport);
}

int ScpiSoltCalibrator::portCount() const
{
    return _portCount;
}

PortStatus ScpiSoltCalibrator::portStatus(int channel, int port) const
{
    if (checkPort(port))
        return {};

    return _channelPorts[channel][port - 1];
}

QVector<double> ScpiSoltCalibrator::vnaData(int channel, int trace) const
{
    QVector<double> vnaData;
    auto data = _session.readData(channel, trace);

    vnaData.reserve(data.size() / 2);

    for (size_t i = 0; i < data.size(); i += 2)
        vnaData.push_back(data[i].toDouble());

    return vnaData;
}

void ScpiSoltCalibrator::reset(int channel)
{
    _session.reset(channel);

    for (auto &ports: _channelPorts)
        for (auto &port: ports)
            clearStatus(port);
}

void ScpiSoltCalibrator::solt2Calibration(int channel, int port1, int port2) const
{
    if (checkPort(port1)
       || checkPort(port2)
       || (port1 == port2))
        return;

    _session.solt2Calibration(channel, port1, port2);
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

bool ScpiSoltCalibrator::checkPort(int port) const
{
    return port <= 0 || _portCount < port;
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
