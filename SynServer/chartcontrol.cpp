#include "chartcontrol.h"

using namespace QtCharts;

ChartControl::ChartControl(QObject *chart, QObject *parent) :
    QObject(parent),
    _chart(chart) { }

void ChartControl::initAxis()
{
    const double minFrequency = _channelInfo.minFrequency(m_channel) / 1e9;
    const double maxFrequency = _channelInfo.maxFrequency(m_channel) / 1e9;

    QAbstractAxis *axisY;
    bool status = QMetaObject::invokeMethod(_chart, "axisY",
                                            Q_RETURN_ARG(QAbstractAxis*, axisY));
    _axisY = qobject_cast<QValueAxis *>(axisY);

    _axisY->setRange(-50, 50);
    _axisY->setTickCount(11);

    QAbstractAxis *axisX;
    status = QMetaObject::invokeMethod(_chart, "axisX",
                                            Q_RETURN_ARG(QAbstractAxis*, axisX));
    _axisX = qobject_cast<QValueAxis *>(axisX);
    _axisX->setTitleText("Frequency");
    _axisX->setRange(minFrequency, maxFrequency);
    _axisX->setTickCount(9);

    const int points = _channelInfo.pointsCount(m_channel);
    const double delta = (maxFrequency - minFrequency) / points;
    _frequency.reserve(points);
    for (int i = 0; i < points; ++i) {
        _frequency.push_back(i * delta);
    }
}

void ChartControl::initTraces()
{
    const int traceCount = _channelInfo.traceCount(m_channel);
    _traces.reserve(traceCount);

    for (size_t trace = 1; trace <= traceCount; ++trace) {
       QAbstractSeries* traceSeries;
       const bool status = QMetaObject::invokeMethod(_chart, "createSeries",
                    Q_RETURN_ARG(QAbstractSeries*, traceSeries),
                    Q_ARG(int, 0),
                    Q_ARG(QString, _traceInfo.measurementParameter(m_channel, trace)));

        _traces.push_back(qobject_cast<QLineSeries *>(traceSeries));
    }
}

void ChartControl::updateData()
{
    const int traceCount = _channelInfo.traceCount(m_channel);

    for (size_t trace = 1; trace <= traceCount &&
         _traces.size() < traceCount; ++trace) {
        QAbstractSeries* traceSeries;
        const bool status = QMetaObject::invokeMethod(_chart, "createSeries",
                     Q_RETURN_ARG(QAbstractSeries*, traceSeries),
                     Q_ARG(int, 0),
                     Q_ARG(QString, _traceInfo.measurementParameter(m_channel, trace)));

         _traces.push_back(qobject_cast<QLineSeries *>(traceSeries));
         continue;
    }

    if (traceCount < _traces.size()) {
        for (size_t trace = traceCount; trace < _traces.size() + 1; ++trace) {
            const bool status = QMetaObject::invokeMethod(_chart, "removeSeries",
                         Q_ARG(QAbstractSeries*, _traces.last()));
            _traces.removeLast();
        }
    }

    for (size_t trace = 1; trace <= traceCount; ++trace) {
        _traces[trace - 1]->setName(_traceInfo.measurementParameter(m_channel, trace));

        QVector<double> data = _calibrator.vnaData(m_channel, trace);

        QVector<QPointF> points;
        for (int i = 0; i < data.length(); ++i) {
            points.push_back({
                _frequency[i],
                data[i]
            });
        }
        _traces[trace - 1]->replace(points);
    }
}

void ChartControl::clear()
{
    const bool status = QMetaObject::invokeMethod(_chart, "removeAllSeries");

    _axisX = nullptr;
    _axisY = nullptr;

    _traces.clear();
}
