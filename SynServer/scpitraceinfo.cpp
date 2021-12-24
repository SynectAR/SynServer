#include "scpitraceinfo.h"

ScpiTraceInfo::ScpiTraceInfo() { }

TraceFormat ScpiTraceInfo::format() const
{
    return _traceFormats[_session.format()];
}

int ScpiTraceInfo::number() const
{
    return _session.number();
}

QString ScpiTraceInfo::measurementParameter() const
{
    return _session.measurementParameter(1).chopped(1);
}

double ScpiTraceInfo::scale() const
{
    return _session.scale();
}
