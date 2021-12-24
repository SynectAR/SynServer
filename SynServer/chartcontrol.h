#ifndef CHARTCONTROL_H
#define CHARTCONTROL_H

#include "scpisoltcalibrator.h"

#include <QObject>

namespace QtCharts {
class QLineSeries;
class QValueAxis;
}

class ChartControl : public QObject
{
    Q_OBJECT
public:
    explicit ChartControl(QObject *chart, QObject *parent = nullptr);

public slots:
    void updateData();
    void clear();

private:
    QObject *_chart {nullptr};
    QtCharts::QLineSeries *_series {nullptr};
    QtCharts::QValueAxis *_axisX {nullptr};
    QtCharts::QValueAxis *_axisY {nullptr};

    ScpiSoltCalibrator _calibrator;
    QVector<double> _frequency;
};

#endif // CHARTCONTROL_H
