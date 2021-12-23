#ifndef SCPICHANNELINFO_H
#define SCPICHANNELINFO_H

#include "ichannelinfo.h"

#include "scpisocketsession.h"

#include <QMap>

class ScpiChannelInfo : public IChannelInfo
{
public:
    ScpiChannelInfo();

    double bandwidth() const override;
    int channelCount() const override;
    double frequencyCenter() const override;
    double frequencySpan() const override;
    bool isReady() const override;
    QVector<int> listPorts() const override;
    double maxFrequency() const override;
    double maxPower() const override;
    double minFrequency() const override;
    double minPower() const override;
    int pointsCount() const override;
    double power() const override;
    double powerCenter() const override;
    double powerSpan() const override;
    bool rfOut() const override;
    SweepType sweepType() const override;
    int traceCount() const override;
    TriggerMode triggerMode() const override;
    TriggerScope triggerScope() const override;
    TriggerSource triggerSource() const override;

private:
    ScpiSocketSession _session;
    int _layoutChannels[16] {
        1, 2, 2, 3, 3, 3, 4, 4, 6, 6, 8, 8, 9, 12, 12, 16
    };
    QMap<QString, SweepType> _sweepTypes {
        { "LIN", SweepType::linear },
        { "LOG", SweepType::logarithmic },
        { "POW", SweepType::power },
        { "SEGM", SweepType::segment }
    };
    QMap<QString, TriggerScope> _triggerScopes {
        { "ACT", TriggerScope::active },
        { "ALL", TriggerScope::all }
    };
    QMap<QString, TriggerSource> _triggerSources {
        { "INT", TriggerSource::internal },
        { "EXT", TriggerSource::external },
        { "BUS", TriggerSource::bus },
        { "MAN", TriggerSource::manual }
    };
};

#endif // SCPICHANNELINFO_H
