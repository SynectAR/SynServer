#include "tempsoltcalibrator.h"
#include <QDebug>

TempSoltCalibrator::TempSoltCalibrator()
{
}

void TempSoltCalibrator::apply()
{
    for (auto i : ports) {
        qDebug() << "\nopen = " << i.OPEN << "\nshort = " << i.SHORT << "\nload = " << i.LOAD << "\n";
    }

}

QString TempSoltCalibrator::deviceInfo() const
{
    QString device = "mock device";
    return device;
}

void TempSoltCalibrator::measurePort(Measure measure, int port)
{
        if (measure == Measure::OPEN) {
            ports[port - 1].OPEN = {true};
        } else if (measure == Measure::LOAD) {
            ports[port - 1].LOAD = {true};
        } else if (measure == Measure::SHORT) {
            ports[port - 1].SHORT = {true};
        }
}

void TempSoltCalibrator::measureThru(int srcport, int rcvport) const
{

}

int TempSoltCalibrator::portCount() const
{
    return 2;
}

PortStatus TempSoltCalibrator::portStatus(int port) const
{
    return ports[port - 1];
}

void TempSoltCalibrator::reset()
{

}
