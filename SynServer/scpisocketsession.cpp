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


QStringList ScpiSocketSession::readData() const
{
    return runQuery("CALC:DATA:FDAT?\n").split(',');
}

QStringList ScpiSocketSession::readFrequency() const
{
    return runQuery("SENS:FREQ:DATA?\n").split(',');
}

void ScpiSocketSession::reset() const
{
    runCommand("SENS:CORR:COLL:CLE\n");
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

void ScpiSocketSession::setBandWidth(uint bandWidth) const
{
    runCommand(QString("SENS:BWID %1\n")
               .arg(bandWidth)
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
