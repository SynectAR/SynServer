#ifndef SCPICHANNELINFO_H
#define SCPICHANNELINFO_H

#include "ichannelinfo.h"

#include "scpisocketsession.h"

#include <QMap>

class ScpiChannelInfo : public IChannelInfo
{
public:
    ScpiChannelInfo();

    double bandwidth(int channel) const override;
    CalibrationType calibrationType(int channel) const override;
    int channelCount() const override;
    double frequencyCenter(int channel) const override;
    double frequencySpan(int channel) const override;
    bool isReady() const override;
    QVector<int> listPorts(int channel) const override;
    double maxFrequency(int channel) const override;
    double maxPower(int channel) const override;
    double minFrequency(int channel) const override;
    double minPower(int channel) const override;
    int pointsCount(int channel) const override;
    double power(int channel) const override;
    double powerCenter(int channel) const override;
    double powerSpan(int channel) const override;
    bool rfOut() const override;
    SweepType sweepType(int channel) const override;
    int traceCount(int channel) const override;
    TriggerMode triggerMode() const override;
    TriggerScope triggerScope() const override;
    TriggerSource triggerSource() const override;

private:
    bool isChannelCorrect(int channel) const;

private:
    ScpiSocketSession _session;

    QMap<QString, CalibrationType> _calibrationTypes {
        { "NONE",  CalibrationType::none },
        { "1PATH",  CalibrationType::onePath },
        { "RESPO",  CalibrationType::respO },
        { "RESPS",  CalibrationType::respS },
        { "RESPT",  CalibrationType::respT },
        { "SOLT1",  CalibrationType::solt1 },
        { "SOLT2",  CalibrationType::solt2 }
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
