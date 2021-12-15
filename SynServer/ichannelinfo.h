#ifndef ICHANNELINFO_H
#define ICHANNELINFO_H

#include <QObject>

enum class TriggerSource
{
    INTERNAL,
    EXTERNAL,
    MANUAL,
    BUS
};

class IChannelInfo : public QObject
{
    Q_OBJECT
public:
    virtual ~IChannelInfo() = default;

    virtual int channelCount() const = 0;
    virtual double bandwidth() const = 0;
    virtual double power() const = 0;
    virtual bool rfOut() const = 0;
    virtual int traceCount() const = 0;
    virtual TriggerSource triggerSource() const = 0;


};



#endif // ICHANNELINFO_H
