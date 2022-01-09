#include "chartcontrol.h"

#include "scpichannelinfo.h"
#include "scpisoltcalibrator.h"

#include <QAbstractSeries>
#include <QLineSeries>
#include <QValueAxis>

using namespace QtCharts;

ChartControl::ChartControl(QObject *chart, QObject *parent) :
    QObject(parent),
    _chart(chart)
{
    QAbstractSeries *series {nullptr};
    bool f = QMetaObject::invokeMethod(_chart, "series",
            Q_RETURN_ARG(QAbstractSeries*, series),
            Q_ARG(QString, "S11"));
    Q_ASSERT(f && series);
    _series = qobject_cast<QLineSeries*>(series);

    for (auto axis : _series->attachedAxes()) {
        axis->metaObject()->className();
        if ((axis->alignment() & Qt::AlignBottom) != 0)
            _axisX = qobject_cast<QValueAxis*>(axis);
        if ((axis->alignment() & Qt::AlignLeft) != 0)
            _axisY = qobject_cast<QValueAxis*>(axis);
    }

    ScpiChannelInfo info;
    const auto minFrequency = info.minFrequency(1) / 1e9;
    const auto maxFrequency = info.maxFrequency(1) / 1e9;
    const auto points = info.pointsCount(1);
    const auto delta = (maxFrequency - minFrequency) / points;

    _axisY->setTitleText("S11");
    _axisY->setRange(-50, 50);
    _axisY->setTickCount(11);

    _axisX->setTitleText("Frequency");
    _axisX->setRange(minFrequency, maxFrequency);
    _axisX->setTickCount(9);

    _frequency.reserve(points);
    for (int i = 0; i < points; ++i) {
        _frequency.push_back(i * delta);
    }
}

void ChartControl::updateData()
{
    // todo: add channel and trace
    QVector<double> data = _calibrator.vnaData(1, 1);

    QVector<QPointF> points;
    for (int i = 0; i < data.length(); ++i) {
        points.push_back({
            _frequency[i],
            data[i]
        });
    }
    _series->replace(points);
}

void ChartControl::clear()
{
    _series->clear();
}
