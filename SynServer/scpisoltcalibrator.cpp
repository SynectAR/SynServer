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
    if (!isChannelCorrect(channel))
        return;

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
    if (!isChannelCorrect(channel) || !isPortCorrect(port))
        return;

    _session.clear();
    _session.chooseCalibrationSubclass(channel, 1);
    _session.measurePort(_measureName[measure], channel, port);

    qDebug() << _session.errorCode();
    if (_session.errorCode() != 0)
        return;

    switch (measure) {
    case Measure::OPEN:
        _channelPorts[channel - 1][port - 1].OPEN = true;
        break;
    case Measure::SHORT:
        _channelPorts[channel - 1][port - 1].SHORT = true;
        break;
    case Measure::LOAD:
        _channelPorts[channel - 1][port -1].LOAD = true;
        break;
    }
}

void ScpiSoltCalibrator::measureThru(int channel, int srcport, int rcvport)
{
    if (!isChannelCorrect(channel)
            || !isPortCorrect(srcport)
            || !isPortCorrect(rcvport)
            || (rcvport == srcport))
        return;

    _channelPorts[channel - 1][srcport - 1].THRU[rcvport - 1] = true;
    _channelPorts[channel - 1][rcvport - 1].THRU[srcport - 1] = true;


    _session.measureThru(channel, srcport, rcvport);
}

int ScpiSoltCalibrator::portCount() const
{
    return _portCount;
}

PortStatus ScpiSoltCalibrator::portStatus(int channel, int port) const
{
    return _channelPorts[channel - 1][port - 1];
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
    if (!isChannelCorrect(channel))
        return;

    _session.reset(channel);

    for (auto &ports: _channelPorts)
        for (auto &port: ports)
            clearStatus(port);
}

void ScpiSoltCalibrator::soltCalibration(int channel, const QVector<int> &ports) const
{
    if (!isChannelCorrect(channel))
        return;

    QVector<int> portsCount(16, 0);
    for (const int port: ports) {
        if (!isPortCorrect(port))
            return;

        ++portsCount[port];
    }

    for (const int count: portsCount)
        if (count > 1)
            return;

    _session.soltCalibration(channel, ports);
}

void ScpiSoltCalibrator::chooseCalibrationKit(int kit) const
{
    if (1 <= kit && kit <= 64)
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

bool ScpiSoltCalibrator::isChannelCorrect(int channel) const
{
    return 1 <= channel && channel <= 16;
}

bool ScpiSoltCalibrator::isPortCorrect(int port) const
{
    return 1 <= port && port <= _portCount;
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
