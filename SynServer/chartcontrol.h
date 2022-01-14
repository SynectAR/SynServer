#ifndef CHARTCONTROL_H
#define CHARTCONTROL_H

#include "scpichannelinfo.h"
#include "scpisoltcalibrator.h"
#include "scpitraceinfo.h"

#include <QAbstractSeries>
#include <QLineSeries>
#include <QObject>
#include <QValueAxis>
#include <QVector>

namespace QtCharts {
class QLineSeries;
class QValueAxis;
}

class ChartControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int channel MEMBER m_channel NOTIFY channelChanged)
public:
    explicit ChartControl(QObject *chart, QObject *parent = nullptr);

public slots:
    void clear();
    void initAxis();
    void initTraces();
    void updateData();

signals:
    void channelChanged();

private:
    int m_channel {1};

    QObject *_chart {nullptr};

    QVector<QtCharts::QLineSeries *> _traces;

    QtCharts::QValueAxis *_axisX {nullptr};
    QtCharts::QValueAxis *_axisY {nullptr};

    ScpiSoltCalibrator _calibrator;
    ScpiChannelInfo _channelInfo;
    ScpiTraceInfo _traceInfo;

    QVector<double> _frequency;
};

#endif // CHARTCONTROL_H
