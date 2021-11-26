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

bool ScpiSocketSession::apply() const
{
    // todo: return success result
    // Рассчитать калибровочные коэффициенты на основании калибровочных мер
    runCommand("SENS:CORR:OFFS:COLL:SAVE\n");
    return false;
}

bool ScpiSocketSession::chooseCalibrationStandard() const
{
    // todo: return success result

    //runCommand("SENS:CORR:COLL:CKIT:ORD:LOAD 1,1\n");

    runCommand("SENS:CORR:COLL:CKIT 1\n");
    qDebug() << "Kit description: " << runQuery("SENS:CORR:COLL:CKIT:DESC?\n");

    runCommand("SENS:CORR:COLL:SUBC 1\n");
    qDebug() << "Kit label: " << runQuery("SENS:CORR:COLL:CKIT:LAB?\n");

    return false;
}

bool ScpiSocketSession::calibrate() const
{
    // todo: return success result

    chooseCalibrationStandard(); //Choose 8503

    QString methodCommand = "SENS:CORR:COLL:METH:LOAD 1\n"; // SOLT2 | SOLT1 | OPEN ...
    // Выбрать метод калибровки type для порта port
    runCommand(methodCommand);


    qDebug() << "Coefficients: " << runQuery("SENS:CORR:COEF? ER,1,1\n");


    measurePort(1, "LOAD");

    // todo: Is it necessary command
    runCommand("SYST:CORR OFF\n");


    //runCommand("SENS:CORR:OFFS:COLL:SAVE\n");
    apply();
    qDebug() << "Coefficients: " << runQuery("SENS:CORR:COEF? ER,1,1\n");

    /*
     _socket->write("SENS:CORR:COLL:METH:SOLT2 1,2\n");

    _socket->write("SENS:CORR:COLL:CKIT:ORD:OPEN 1,1\n"); // Sets or reads out the number of the calibration standard in the calibration kit
    _socket->write("SENS:CORR:OFFS:COLL:OPEN 1\n"); // Measure

    _socket->write("SENS:CORR:COLL:CKIT:ORD:SHORT 1,1\n");
    _socket->write("SENS:CORR:OFFS:COLL:SHORT 1\n");

    _socket->write("SENS:CORR:COLL:CKIT:ORD:LOAD 1,1\n");
    _socket->write("SENS:CORR:OFFS:COLL:LOAD 1\n");

    _socket->write("SENS:CORR:COLL:CKIT:ORD:OPEN 2,1\n");
    _socket->write("SENS:CORR:OFFS:COLL:OPEN 1\n");

    _socket->write("SENS:CORR:COLL:CKIT:ORD:SHORT 2,1\n");
    _socket->write("SENS:CORR:OFFS:COLL:SHORT 1\n");

    _socket->write("SENS:CORR:COLL:CKIT:ORD:LOAD 2,1\n");
    _socket->write("SENS:CORR:OFFS:COLL:LOAD 1\n");

    _socket->write("SENS:CORR:COLL:CKIT:ORD:THRU 1,2,1\n");
    _socket->write("SENS:CORR:OFFS:COLL:THRU 1\n");
    */

    // SENS:CORR:COEF
    //_socket->write();




    return false;
}

QString ScpiSocketSession::deviceInfo() const
{
    return runQuery("*IDN?\n");
}

int ScpiSocketSession::portCount() const
{
    return runQuery("SERV:PORT:COUN?\n").toInt();
}

QString ScpiSocketSession::measurePort(int port, QString type) const
{
    QString measureCommand = "SENS:CORR:OFFS:COLL:LOAD 1,1\n";
    // Измерить калибровочные данные методом type на порте port
    runCommand(measureCommand);

    qDebug() << "Coefficients: " << runQuery("SENS:CORR:COEF? ER,1,1\n");
    return "_";
}

QString ScpiSocketSession::measureThru() const
{
    // todo: is it necessary to specify callibration type SENS:CORR:COLL:METH:THRU
    runCommand("SENS:CORR:OFFS:COLL:THRU 1,2\n");
    return "";
}

QString ScpiSocketSession::portStatus() const
{
    // todo: Is it correct SCPI-command
    auto t =  runQuery("SENS:CORR:COLL:CKIT:CONN:CAT?\n");

    return t;
}

bool ScpiSocketSession::reset() const
{
    // todo: implement
    // SENS:CORR:COLL:CLE
    return false;
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
