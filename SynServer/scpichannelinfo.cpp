#include "scpichannelinfo.h"

ScpiChannelInfo::ScpiChannelInfo() {}

double ScpiChannelInfo::bandwidth(int channel) const
{
    return _session.bandwidth(channel);
}

CalibrationType ScpiChannelInfo::calibrationType(int channel) const
{
    return _calibrationTypes[_session.calibrationType(channel)];
}

int ScpiChannelInfo::channelCount() const
{
    return _layoutChannels[_session.channelLayout() - 1];
}

double ScpiChannelInfo::frequencyCenter(int channel) const
{
    return _session.frequencyCenter(channel);
}

double ScpiChannelInfo::frequencySpan(int channel) const
{
    return _session.frequncySpan(channel);
}

bool ScpiChannelInfo::isReady() const
{
    return _session.isReady();
}

QVector<int> ScpiChannelInfo::listPorts(int channel) const
{
    QSet<int> ports;

    QRegExp rx("(\\d+)");
    for (size_t trace = 1; trace <= traceCount(channel); ++trace) {
        auto parameter = _session.measurementParameter(channel, trace);
        bool split = parameter[0] == 'S';

        int pos = 0;
        while ((pos = rx.indexIn(parameter, pos)) != -1) {
            auto port = rx.cap(1);
            if (split) {
                int leftDigits = port.size() / 2;
                ports.insert(port.left(leftDigits).toInt());
                ports.insert(port.right(port.size() - leftDigits).toInt());
            } else {
                ports.insert(port.toInt());
            }

            pos += rx.matchedLength();
        }
    }

    return QVector<int>(ports.cbegin(), ports.cend());
}

double ScpiChannelInfo::maxFrequency(int channel) const
{
    return _session.maxFrequency(channel);
}

double ScpiChannelInfo::maxPower(int channel) const
{
    return _session.maxPower(channel);
}

double ScpiChannelInfo::minFrequency(int channel) const
{
    return _session.minFrequency(channel);
}

double ScpiChannelInfo::minPower(int channel) const
{
    return _session.minPower(channel);
}

int ScpiChannelInfo::pointsCount(int channel) const
{
    return _session.pointsCount(channel);
}

double ScpiChannelInfo::power(int channel) const
{
    return _session.power(channel);
}

double ScpiChannelInfo::powerCenter(int channel) const
{
    return _session.powerCenter(channel);
}

double ScpiChannelInfo::powerSpan(int channel) const
{
    return _session.powerSpan(channel);
}

bool ScpiChannelInfo::rfOut() const
{
    return _session.rfOut();
}

SweepType ScpiChannelInfo::sweepType(int channel) const
{
    return _sweepTypes[_session.sweepType(channel)];
}

int ScpiChannelInfo::traceCount(int channel) const
{
    return _session.traceCount(channel);
}

TriggerMode ScpiChannelInfo::triggerMode() const
{
    if (_session.isTriggerContinuous())
        return TriggerMode::continuous;

    return TriggerMode::hold;
}

TriggerScope ScpiChannelInfo::triggerScope() const
{
    return _triggerScopes[_session.triggerScope()];
}

TriggerSource ScpiChannelInfo::triggerSource() const
{
    return _triggerSources[_session.triggerSource()];
}

