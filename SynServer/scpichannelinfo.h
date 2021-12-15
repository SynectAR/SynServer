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
    double power() const override;
    bool rfOut() const override;
    int traceCount() const;
    TriggerSource triggerSource() const override;

private:
    ScpiSocketSession _session;
    QMap<QString, TriggerSource> _triggerSources {
        { "INT", TriggerSource::INTERNAL },
        { "EXT", TriggerSource::EXTERNAL },
        { "BUS", TriggerSource::BUS },
        { "MAN", TriggerSource::MANUAL }
    };
};

#endif // SCPICHANNELINFO_H
