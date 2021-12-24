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

    virtual TraceFormat format() const = 0;
    virtual int number() const = 0;
    virtual QString measurementParameter() const = 0;
    virtual double scale() const = 0;
};

#endif // ITRACEINFO_H
