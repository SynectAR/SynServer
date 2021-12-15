#include "chartcontrol.h"
#include "scpisoltcalibrator.h"
#include "server.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QQmlContext>
#include <QScopedPointer>

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
                     [&server, &calibrator] () {
       server.sendMessage(calibrator.deviceInfo());
    });

    auto context = engine.rootContext();
    context->setContextProperty("calibrator", &calibrator);

    auto root = engine.rootObjects().first();
    auto chartObject = root->findChild<QObject *>("chart");
    auto *chart = new ChartControl(chartObject, &app);
    context->setContextProperty("chartControl", chart);

    return app.exec();
}
