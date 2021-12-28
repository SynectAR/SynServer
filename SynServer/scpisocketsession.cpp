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

double ScpiSocketSession::bandwidth(int channel) const
{
    return runQuery(QString("SENS%1:BAND?\n")
                    .arg(channel)).toDouble();
}

QString ScpiSocketSession::calibrationType(int channel) const
{
    const auto fullType = runQuery(QString("SENS%1:CORR:TYPE?\n")
                                   .arg(channel)).chopped(1).split(',');
    return fullType[0];
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

double ScpiSocketSession::frequencyCenter(int channel) const
{
    return runQuery(QString("SENS%1:FREQ:CENT?\n")
                    .arg(channel)).toDouble();
}

double ScpiSocketSession::frequncySpan(int channel) const
{
    return runQuery(QString("SENS%1:FREQ:SPAN?\n")
                    .arg(channel)).toDouble();
}

QString ScpiSocketSession::getSubclassGender(int subclass) const
{
    // todo: get from scpi
    return "M";
}

bool ScpiSocketSession::isReady() const
{
    return static_cast<bool>(runQuery("SYST:READ?\n").toInt());
}

bool ScpiSocketSession::isTriggerContinuous() const
{
    return static_cast<bool>(runQuery("INIT:CONT?\n").toInt());
}

double ScpiSocketSession::maxFrequency(int channel) const
{
    return runQuery(QString("SENS%1:FREQ:STOP?\n")
                    .arg(channel)).toDouble();
}

double ScpiSocketSession::maxPower(int channel) const
{
    return runQuery(QString("SOUR%1:POW:STOP?\n")
                    .arg(channel)).toDouble();
}

double ScpiSocketSession::minFrequency(int channel) const
{
    return runQuery(QString("SENS%1:FREQ:STAR?\n")
                    .arg(channel)).toDouble();
}

double ScpiSocketSession::minPower(int channel) const
{
    return runQuery(QString("SENS%1:POW:STAR?\n")
                    .arg(channel)).toDouble();
}

QString ScpiSocketSession::measurementParameter(int channel, int trace) const
{
    return runQuery(QString("CALC%1:PAR%2:DEF?\n")
                    .arg(channel)
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

int ScpiSocketSession::pointsCount(int channel) const
{
    return runQuery(QString("SENS%1:SWE:POIN?\n")
                    .arg(channel)).toInt();
}

int ScpiSocketSession::portCount() const
{
    return runQuery("SERV:PORT:COUN?\n").toInt();
}

double ScpiSocketSession::power(int channel) const
{
    return runQuery(QString("SOUR%1:POW?\n")
                    .arg(channel)).toDouble();
}

double ScpiSocketSession::powerCenter(int channel) const
{
    return runQuery(QString("SENS%1:POW:CENT?\n")
                    .arg(channel)).toDouble();
}

double ScpiSocketSession::powerSpan(int channel) const
{
    return runQuery(QString("SENS%1:POW:SPAN?\n")
                    .arg(channel)).toDouble();
}

QStringList ScpiSocketSession::readData() const
{
    auto data = runQuery("CALC:DATA:FDAT?\n");
    runQuery("*OPC?\n");
    return data.split(',');
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

void ScpiSocketSession::selectActiveTrace() const
{
    runCommand("CALC:PAR:SEL\n");
}

void ScpiSocketSession::selectTraceParameter(QString parameter) const
{
    runCommand(QString("CALC:PAR:DEF %1\n").
               arg(parameter));
}

void ScpiSocketSession::setBandWidth(uint bandWidth) const
{
    runCommand(QString("SENS:BWID %1\n")
               .arg(bandWidth)
               .toUtf8());
}

void ScpiSocketSession::setMinFrequency(qreal minFrequency) const
{
    runCommand(QString("SENS:FREQ:STAR %1GHZ\n")
               .arg(minFrequency)
               .toUtf8());
}

void ScpiSocketSession::setMaxFrequency(qreal maxFrequency) const
{
    runCommand(QString("SENS:FREQ:STOP %1GHZ\n")
               .arg(maxFrequency)
               .toUtf8());
}

void ScpiSocketSession::setPointNumber(uint pointNumber) const
{
    runCommand(QString("SENS:SWE:POIN %1\n")
               .arg(pointNumber)
               .toUtf8());
}

void ScpiSocketSession::setReadTraceFormat(QString format) const
{
    runCommand(QString("CALC:FORM %1\n")
               .arg(format));
}

void ScpiSocketSession::solt2Calibration(int port1, int port2) const
{
    runCommand(QString("SENS:CORR:COLL:METH:SOLT2 %1,%2\n")
               .arg(port1)
               .arg(port2));
}

QString ScpiSocketSession::sweepType(int channel) const
{
    return runQuery(QString("SENS%1:SWE:TYPE?\n")
                    .arg(channel)).chopped(1);
}

int ScpiSocketSession::traceCount(int channel) const
{
    return runQuery(QString("CALC%1:PAR:COUN?\n")
                    .arg(channel)).toInt();
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
