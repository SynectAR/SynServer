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

double ScpiChannelInfo::power() const
{
    return _session.power();
}

bool ScpiChannelInfo::rfOut() const
{
    return _session.rfOut();
}

int ScpiChannelInfo::traceCount() const
{
    return _session.traceCount();
}

TriggerSource ScpiChannelInfo::triggerSource() const
{
    return _triggerSources[_session.triggerSource()];
}
