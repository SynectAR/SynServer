#ifndef SCPITRACEINFO_H
#define SCPITRACEINFO_H

#include "itraceinfo.h"

#include "scpisocketsession.h"

#include <QMap>

class ScpiTraceInfo : public ITraceInfo
{
public:
    ScpiTraceInfo();

    TraceFormat format() const override;
    int number() const override;
    QString measurementParameter() const override;
    double scale() const override;

private:
    ScpiSocketSession _session;

    QMap<QString, TraceFormat> _traceFormats {
        { "GDEL", TraceFormat::gdelay },
        { "IMAG", TraceFormat::imaginary },
        { "MLIN", TraceFormat::mlinear },
        { "MLOG", TraceFormat::mlogarithmic },
        { "PHAS", TraceFormat::phase },
        { "PLIN", TraceFormat::plinear },
        { "PLOG", TraceFormat::plogarithmic },
        { "POL", TraceFormat::polar },
        { "REAL", TraceFormat::real },
        { "SADM", TraceFormat::sadmittance },
        { "SCOM", TraceFormat::scomplex },
        { "SLIN", TraceFormat::slinear },
        { "SLOG", TraceFormat::slogarithmic },
        { "SMIT", TraceFormat::smith },
        { "SWR", TraceFormat::swr },
        { "UPH", TraceFormat::uphase }
    };
};

#endif // SCPITRACEINFO_H
