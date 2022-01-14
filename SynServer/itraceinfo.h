#ifndef ITRACEINFO_H
#define ITRACEINFO_H

#include <QObject>

enum class TraceFormat
{
    mlogarithmic,
    phase,
    gdelay,
    slinear,
    slogarithmic,
    scomplex,
    smith,
    sadmittance,
    plinear,
    plogarithmic,
    polar,
    mlinear,
    swr,
    real,
    imaginary,
    uphase
};

class ITraceInfo : public QObject
{
    Q_OBJECT
public:
    virtual ~ITraceInfo() = default;

    virtual TraceFormat format(int channel, int trace) const = 0;
    virtual int number(int channel) const = 0;
    virtual QString measurementParameter(int channel, int trace) const = 0;
    virtual double scale(int channel, int trace) const = 0;
};

#endif // ITRACEINFO_H
