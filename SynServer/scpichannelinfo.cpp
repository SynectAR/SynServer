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
    // todo:
    return 0;
}

double ScpiChannelInfo::frequencySpan() const
{
    // todo:
    return 0;
}

double ScpiChannelInfo::maxFrequency() const
{
    // todo:
    return 0;
}

double ScpiChannelInfo::maxPower() const
{
    // todo:
    return 0;
}

double ScpiChannelInfo::minFrequency() const
{
    // todo:
    return 0;
}

double ScpiChannelInfo::minPower() const
{
    // todo:
    return 0;
}

int ScpiChannelInfo::pointsCount() const
{
    // todo:
    return 0;
}

double ScpiChannelInfo::power() const
{
    return _session.power();
}

double ScpiChannelInfo::powerCenter() const
{
    // todo:
    return 0;
}

double ScpiChannelInfo::powerSpan() const
{
    // todo:
    return 0;
}

bool ScpiChannelInfo::rfOut() const
{
    return _session.rfOut();
}

SweepType ScpiChannelInfo::sweepType() const
{
    // todo:
    return SweepType::linear;
}

int ScpiChannelInfo::traceCount() const
{
    return _session.traceCount();
}

TriggerSource ScpiChannelInfo::triggerSource() const
{
    return _triggerSources[_session.triggerSource()];
}
