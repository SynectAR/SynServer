#include "scpisoltcalibrator.h"
#include "server.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QQmlContext>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    MyTcpServer server;
    server.startListening();

    ScpiSoltCalibrator calibrator;
    QObject::connect(&server, &MyTcpServer::peerConnected,
                     &server, [&server, &calibrator] () {
       server.sendMessage(calibrator.deviceInfo());
    });

    calibrator.vnaData();

    calibrator.measurePort(Measure::OPEN, 1);
    calibrator.measurePort(Measure::SHORT, 1);
    calibrator.measurePort(Measure::LOAD, 1);

    calibrator.measurePort(Measure::OPEN, 2);
    calibrator.measurePort(Measure::SHORT, 2);
    calibrator.measurePort(Measure::LOAD, 2);

    calibrator.measureThru(1, 2);
    calibrator.apply();

    auto context = engine.rootContext();
    context->setContextProperty("calibrator", &calibrator);

    return app.exec();
}
