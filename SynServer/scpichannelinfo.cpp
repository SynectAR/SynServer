#include "scpichannelinfo.h"

ScpiChannelInfo::ScpiChannelInfo() {}

double ScpiChannelInfo::bandwidth() const
{
    return _session.bandwidth();
}

int ScpiChannelInfo::channelCount() const
{
    return _layoutChannels[_session.channelLayout() - 1];
}

double ScpiChannelInfo::frequencyCenter() const
{
    return _session.frequencyCenter();
}

double ScpiChannelInfo::frequencySpan() const
{
    return _session.frequncySpan();
}

QVector<int> ScpiChannelInfo::listPorts() const
{
    QVector<int> ports;

    QRegExp rx("(\\d+)");
    for (size_t trace = 1; trace <= traceCount(); ++trace) {
        auto parameter = _session.measurementParameter(trace);
        bool split = parameter[0] == 'S';

        int pos = 0;
        while ((pos = rx.indexIn(parameter, pos)) != -1) {
            auto port = rx.cap(1);
            if (split) {
                int leftDigits = port.size() / 2;
                ports.push_back(port.left(leftDigits).toInt());
                ports.push_back(port.right(port.size() - leftDigits).toInt());
            } else {
                ports.push_back(port.toInt());
            }

            pos += rx.matchedLength();
        }
    }

    return ports;
}

double ScpiChannelInfo::maxFrequency() const
{
    return _session.maxFrequency();
}

double ScpiChannelInfo::maxPower() const
{
    return _session.maxPower();
}

double ScpiChannelInfo::minFrequency() const
{
    return _session.minFrequency();
}

double ScpiChannelInfo::minPower() const
{
    return _session.minPower();
}

int ScpiChannelInfo::pointsCount() const
{
    return _session.pointsCount();
}

double ScpiChannelInfo::power() const
{
    return _session.power();
}

double ScpiChannelInfo::powerCenter() const
{
    return _session.powerCenter();
}

double ScpiChannelInfo::powerSpan() const
{
    return _session.powerSpan();
}

bool ScpiChannelInfo::rfOut() const
{
    return _session.rfOut();
}

SweepType ScpiChannelInfo::sweepType() const
{
    return _sweepTypes[_session.sweepType()];
}

int ScpiChannelInfo::traceCount() const
{
    return _session.traceCount();
}

TriggerScope ScpiChannelInfo::triggerScope() const
{
    return _triggerScopes[_session.triggerScope()];
}

TriggerSource ScpiChannelInfo::triggerSource() const
{
    return _triggerSources[_session.triggerSource()];
}
/*
void ScpiChannelInfo::getBandwidth()
{
    int newBandwidth = _session.bandwidth();
    if (m_bandwidth != newBandwidth) {
        m_bandwidth = newBandwidth;
        emit IChannelInfo::bandwidthChanged(m_bandwidth);
    }
}
*/
