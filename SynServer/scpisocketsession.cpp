#include "scpisocketsession.h"

#include <QDataStream>

ScpiSocketSession::ScpiSocketSession()
    : _socket(new QTcpSocket(this))
{
    _socket->connectToHost(_host, _port);

    connect(_socket, &QAbstractSocket::stateChanged, this,
            [this](QAbstractSocket::SocketState s) {
        if (s == QTcpSocket::ConnectedState) {
            emit connectedToHost();
        }
    });
}

ScpiSocketSession::~ScpiSocketSession()
{
    _socket->disconnectFromHost();
}

void ScpiSocketSession::apply() const
{
    runCommand("SENS:CORR:COLL:SAVE\n");
}

double ScpiSocketSession::bandwidth() const
{
    return runQuery("SENS:BAND?\n").toDouble();
}

void ScpiSocketSession::clear() const
{
    runCommand("*CLS\n");
}

void ScpiSocketSession::chooseCalibrationKit(int kit) const
{
    runCommand(QString("SENS:CORR:COLL:CKIT %1\n")
               .arg(kit));
}

void ScpiSocketSession::chooseCalibrationSubclass(int subclass) const
{
    runCommand(QString("SENS:CORR:COLL:SUBC %1\n")
               .arg(subclass));
}

int ScpiSocketSession::channelLayout() const
{
    return runQuery("DISP:SPL?\n").toInt();
}

QString ScpiSocketSession::deviceInfo() const
{
    return runQuery("*IDN?\n");
}

int ScpiSocketSession::errorCode() const
{
    auto errorMessage = runQuery("SYST:ERR?\n").split(',');
    return errorMessage[0].mid(1).toInt();
}

QString ScpiSocketSession::format() const
{
    return runQuery("CALC:FORM?\n").chopped(1);
}

double ScpiSocketSession::frequencyCenter() const
{
    return runQuery("SENS:FREQ:CENT?\n").toDouble();
}

double ScpiSocketSession::frequncySpan() const
{
    return runQuery("SENS:FREQ:SPAN?\n").toDouble();
}

QString ScpiSocketSession::getSubclassGender(int subclass) const
{
    // todo: get from scpi
    return "M";
}

bool ScpiSocketSession::isTriggerContinuous() const
{
    return static_cast<bool>(runQuery("INIT:CONT?\n").toInt());
}

double ScpiSocketSession::maxFrequency() const
{
    return runQuery("SENS:FREQ:STOP?\n").toDouble();
}

double ScpiSocketSession::maxPower() const
{
    return runQuery("SOUR:POW:STOP?\n").toDouble();
}

double ScpiSocketSession::minFrequency() const
{
    return runQuery("SENS:FREQ:STAR?\n").toDouble();
}

double ScpiSocketSession::minPower() const
{
    return runQuery("SENS:POW:STAR?\n").toDouble();
}

QString ScpiSocketSession::measurementParameter(int trace) const
{
    return runQuery(QString("CALC:PAR%1:DEF?\n")
                    .arg(trace));
}

void ScpiSocketSession::measurePort(QString type, int port) const
{
    runCommand(QString("SENS:CORR:COLL:%1 %2\n")
               .arg(type)
               .arg(port));
}

void ScpiSocketSession::measureThru(int rcvport, int srcport) const
{
    runCommand(QString("SENS:CORR:COLL:THRU %1,%2\n")
               .arg(rcvport)
               .arg(srcport));
    runCommand(QString("SENS:CORR:COLL:THRU %2,%1\n")
               .arg(rcvport)
               .arg(srcport));
}

int ScpiSocketSession::number() const
{
    return runQuery("SERV:CHAN:TRAC:ACT?\n").toInt();
}

int ScpiSocketSession::pointsCount() const
{
    return runQuery("SENS:SWE:POIN?\n").toInt();
}

int ScpiSocketSession::portCount() const
{
    return runQuery("SERV:PORT:COUN?\n").toInt();
}

double ScpiSocketSession::power() const
{
    return runQuery("SOUR:POW?\n").toDouble();
}

double ScpiSocketSession::powerCenter() const
{
    return runQuery("SENS:POW:CENT?\n").toDouble();
}

double ScpiSocketSession::powerSpan() const
{
    return runQuery("SENS:POW:SPAN?\n").toDouble();
}


void ScpiSocketSession::reset() const
{
    runCommand("SENS:CORR:COLL:CLE\n");
}

bool ScpiSocketSession::rfOut() const
{
    return static_cast<bool>(runQuery("OUTP?\n").toInt());
}

double ScpiSocketSession::scale() const
{
    return runQuery("DISP:WIND:TRAC:Y:PDIV?\n").toDouble();
}

void ScpiSocketSession::solt2Calibration(int port1, int port2) const
{
    runCommand(QString("SENS:CORR:COLL:METH:SOLT2 %1,%2\n")
               .arg(port1)
               .arg(port2));
}

QString ScpiSocketSession::sweepType() const
{
    return runQuery("SENS:SWE:TYPE?\n").chopped(1);
}

int ScpiSocketSession::traceCount() const
{
    return runQuery("CALC:PAR:COUN?\n").toInt();
}

QString ScpiSocketSession::triggerScope() const
{
    return runQuery("TRIG:SCOP?\n").chopped(1);
}

QString ScpiSocketSession::triggerSource() const
{
    return runQuery("TRIG:SOUR?\n").chopped(1);
}

void ScpiSocketSession::runCommand(QString command) const
{
    _socket->write(command.toLocal8Bit());
    if (!_socket->waitForBytesWritten(_timeout))
        return;
}

QString ScpiSocketSession::runQuery(QString query) const
{
    _socket->write(query.toLocal8Bit());
    if (!_socket->waitForReadyRead(_timeout))
        return "";
    return _socket->readLine();
}
