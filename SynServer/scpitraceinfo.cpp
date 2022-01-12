#include "scpitraceinfo.h"

ScpiTraceInfo::ScpiTraceInfo() { }

TraceFormat ScpiTraceInfo::format(int channel, int trace) const
{
    return _traceFormats[_session.format(channel, trace)];
}

int ScpiTraceInfo::number(int channel) const
{
    return _session.number(channel);
}

QString ScpiTraceInfo::measurementParameter(int channel, int trace) const
{
    return _session.measurementParameter(channel, trace).chopped(1);
}

double ScpiTraceInfo::scale(int channel, int trace) const
{
    return _session.scale(channel, trace);
}
