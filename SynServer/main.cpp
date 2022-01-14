#include "chartcontrol.h"
#include "scpichannelinfo.h"
#include "scpisoltcalibrator.h"
#include "scpitraceinfo.h"
#include "server.h"
#include "rpcclient.h"
#include "tempsoltcalibrator.h"
#include "scpichannelinfo.h"

#include <qrcodegen.hpp>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QQmlContext>
#include <climits>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QFile>
#include <QString>
#include <QCoreApplication>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    ScpiSoltCalibrator calibrator;

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);

    }, Qt::QueuedConnection);


    engine.load(url);
    qDebug() << calibrator.deviceInfo();
    ScpiChannelInfo channelInfo;
    RpcServer server(calibrator, channelInfo);
    //RpcClient client;
    //client.listPort(1);
   // qDebug() << channelInfo.channelCount();
    auto context = engine.rootContext();
    context->setContextProperty("server", &server);
    context->setContextProperty("calibrator", &calibrator);

    auto root = engine.rootObjects().first();
    auto chartObject = root->findChild<QObject *>("chart");
    auto *chart = new ChartControl(chartObject, &app);
    context->setContextProperty("chartControl", chart);

    return app.exec();
}
