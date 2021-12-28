#ifndef ICHANNELINFO_H
#define ICHANNELINFO_H

#include <QObject>

enum class CalibrationType
{
    respO,
    respS,
    respT,
    solt1,
    solt2,
    onePath,
    none
};

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

    virtual double bandwidth(int channel) const = 0;
    virtual CalibrationType calibrationType(int channel) const = 0;
    virtual int channelCount() const = 0;
    virtual double frequencyCenter(int channel) const = 0;
    virtual double frequencySpan(int channel) const = 0;
    virtual bool isReady() const = 0;
    virtual QVector<int> listPorts(int channel) const = 0;
    virtual double maxFrequency(int channel) const = 0;
    virtual double maxPower(int channel) const = 0;
    virtual double minFrequency(int channel) const = 0;
    virtual double minPower(int channel) const = 0;
    virtual int pointsCount(int channel) const = 0;
    virtual double power(int channel) const = 0;
    virtual double powerCenter(int channel) const = 0;
    virtual double powerSpan(int channel) const = 0;
    virtual bool rfOut() const = 0;
    virtual SweepType sweepType(int channel) const = 0;
    virtual int traceCount(int channel) const = 0;
    virtual TriggerMode triggerMode() const = 0;
    virtual TriggerScope triggerScope() const = 0;
    virtual TriggerSource triggerSource() const = 0;
};

#endif // ICHANNELINFO_H
