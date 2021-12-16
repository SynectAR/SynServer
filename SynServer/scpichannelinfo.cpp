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
