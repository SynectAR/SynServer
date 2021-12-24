#include "chartcontrol.h"

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

    _axisY->setTitleText("S11");
    _axisY->setRange(-50, 50);
    _axisY->setTickCount(11);

    _axisX->setTitleText("Frequency");
    _axisX->setRange(1, 9);
    _axisX->setTickCount(9);

    // todo: Get from SCPI
    const auto minFrequency = 0;
    const auto maxFrequency = 9;
    const auto points = 201.0;
    const auto delta = (maxFrequency - minFrequency) / points;

    _frequency.reserve(points);
    for (int i = 0; i < points; ++i) {
        _frequency.push_back(i * delta);
    }
}

void ChartControl::updateData()
{
    QVector<double> data = _calibrator.vnaData();

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
CMakeLists.txt
Chart.qml
QRcode.qml
chartcontrol.cpp
chartcontrol.h
isoltcalibrator.h
main.cpp
main.qml
qml.qrc
qrcodegen.cpp
qrcodegen.hpp
scpisocketsession.cpp
scpisocketsession.h
scpisoltcalibrator.cpp
scpisoltcalibrator.h
svg_xml.svg
