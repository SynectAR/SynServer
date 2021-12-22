#ifndef ICHANNELINFO_H
#define ICHANNELINFO_H

#include <QObject>

enum class SweepType
{
    linear,
    logarithmic,
    segment,
    power
};

enum class TriggerMode
{
    continuous,
    hold
};

enum class TriggerScope
{
    all,
    active
};

enum class TriggerSource
{
    internal,
    external,
    manual,
    bus
};

class IChannelInfo : public QObject
{
    Q_OBJECT

public:
    virtual ~IChannelInfo() = default;

    virtual double bandwidth() const = 0;
    virtual int channelCount() const = 0;
    virtual double frequencyCenter() const = 0;
    virtual double frequencySpan() const = 0;
    virtual bool isReady() const = 0;
    virtual QVector<int> listPorts() const = 0;
    virtual double maxFrequency() const = 0;
    virtual double maxPower() const = 0;
    virtual double minFrequency() const = 0;
    virtual double minPower() const = 0;
    virtual int pointsCount() const = 0;
    virtual double power() const = 0;
    virtual double powerCenter() const = 0;
    virtual double powerSpan() const = 0;
    virtual bool rfOut() const = 0;
    virtual SweepType sweepType() const = 0;
    virtual int traceCount() const = 0;
    virtual TriggerMode triggerMode() const = 0;
    virtual TriggerScope triggerScope() const = 0;
    virtual TriggerSource triggerSource() const = 0;
};

#endif // ICHANNELINFO_H
