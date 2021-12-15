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

void ScpiSocketSession::chooseCalibrationKit(int kit) const
{
    runCommand(QString("SENS:CORR:COLL:CKIT %1\n")
               .arg(kit));
    qDebug() << "Kit description: " << runQuery("SENS:CORR:COLL:CKIT:DESC?\n");
    qDebug() << "Kit label: " << runQuery("SENS:CORR:COLL:CKIT:LAB?\n");
}

void ScpiSocketSession::chooseCalibrationSubclass(int subclass) const
{
    runCommand(QString("SENS:CORR:COLL:SUBC %1\n")
               .arg(subclass));
    qDebug() << runQuery("SENS:CORR:COLL:SUBC?\n");
}

int ScpiSocketSession::channelCount() const
{
    // todo:
    // "SERV:CHAN:COUN?\n" - maximum number if channels
    // "DISP:SPL?\n" - returns channel window layout. It's necessary to get number of channel from layout number.
    return 0;
}

QString ScpiSocketSession::deviceInfo() const
{
    return runQuery("*IDN?\n");
}

QString ScpiSocketSession::getSubclassGender(int subclass) const
{
    //auto type = runQuery(QString("SENS:CORR:COLL:CKIT:STAN%1:TYPE?\n")
    //                     .arg(subclass));
    //auto label = runQuery(QString("SENS:CORR:COLL:CKIT:STAN%1:LAB?\n")
    //                      .arg(subclass));
    return "M";
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

int ScpiSocketSession::portCount() const
{
    return runQuery("SERV:PORT:COUN?\n").toInt();
}

double ScpiSocketSession::power() const
{
    return runQuery("SOUR:POW?\n").toDouble();
}

void ScpiSocketSession::reset() const
{
    runCommand("SENS:CORR:COLL:CLE\n");
}

bool ScpiSocketSession::rfOut() const
{
    // todo:
    // "OUTP?\n"
    return false;
}

void ScpiSocketSession::solt2Calibration(int port1, int port2) const
{
    runCommand(QString("SENS:CORR:COLL:METH:SOLT2 %1,%2\n")
               .arg(port1)
               .arg(port2));
}

int ScpiSocketSession::traceCount() const
{
    // todo:
    // "CALC:PAR:COUN?\n"
    return 0;
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
