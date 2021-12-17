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
    /*
    Q_PROPERTY(double bandwidth READ bandwidth NOTIFY bandwidthChanged)
    Q_PROPERTY(int channelCount READ channelCount NOTIFY channelCountChanged)
    Q_PROPERTY(double frequencyCenter READ frequencyCenter NOTIFY frequencyCenterChanged)
    Q_PROPERTY(double frequencySpan READ frequencySpan NOTIFY frequencySpanChanged)
    Q_PROPERTY(double maxFrequency READ maxFrequency NOTIFY maxFrequencyChanged)
    Q_PROPERTY(double maxPower READ maxPower NOTIFY maxPowerChanged)
    Q_PROPERTY(double minFrequency READ minFrequency NOTIFY minFrequencyChanged)
    Q_PROPERTY(double minPower READ minPower NOTIFY minPowerChanged)
    Q_PROPERTY(int pointsCount READ pointsCount NOTIFY pointsCountChanged)
    Q_PROPERTY(double power READ power NOTIFY powerChanged)
    Q_PROPERTY(double powerCenter READ powerCenter NOTIFY powerCenterChanged)
    Q_PROPERTY(bool rfOut READ rfOut NOTIFY rfOutChanged)
    Q_PROPERTY(SweepType sweepType READ sweepType NOTIFY sweepTypeChanged)
    Q_PROPERTY(int traceCount READ traceCount NOTIFY traceCountChanged)
    Q_PROPERTY(TriggerScope triggerScope READ triggerScope NOTIFY triggerScopeChanged)
    Q_PROPERTY(TriggerSource triggerSource READ triggerSource NOTIFY triggerSourceChanged)
    */

public:
    virtual ~IChannelInfo() = default;

    virtual double bandwidth() const = 0;
    virtual int channelCount() const = 0;
    virtual double frequencyCenter() const = 0;
    virtual double frequencySpan() const = 0;
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
    virtual TriggerScope triggerScope() const = 0;
    virtual TriggerSource triggerSource() const = 0;

/*
signals:
    void bandwidthChanged(double bandWidth);
    void channelCountChanged(int channelCount);
    void frequencyCenterChanged(double frequencyCenter);
    void frequencySpanChanged(double frequencySpan);
    void maxFrequencyChanged(double maxFrequency);
    void maxPowerChanged(double maxPower);
    void minFrequencyChanged(double minFrequency);
    void minPowerChanged(double minPower);
    void pointsCountChanged(int pointsCount);
    void powerChanged(double power);
    void powerCenterChanged(double powerCenter);
    void powerSpanChanged(double powerSpan);
    void rfOutChanged(bool rfOut);
    void sweepTypeChanged(SweepType sweepType);
    void traceCountChanged(int traceCount);
    void triggerScopeChanged(TriggerScope scope);
    void triggerSourceChanged(TriggerSource source);

protected:
    double m_bandwidth;
    int m_channelCount;
    double m_frequencyCenter;
    double m_frequencySpan;
    double m_maxFrequency;
    double m_maxPower;
    double m_minFrequency;
    double m_minPower;
    int m_pointsCount;
    double m_power;
    double m_powerCenter;
    bool m_rfOut;
    SweepType m_sweepType;
    int m_traceCount;
    TriggerScope m_triggerScope;
    TriggerSource m_triggerSource;
*/
};

#endif // ICHANNELINFO_H
