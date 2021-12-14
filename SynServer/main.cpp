#include "scpisoltcalibrator.h"
#include "server.h"
#include "rpcclient.h"

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


    TempSoltCalibrator calibrator;
    RpcServer server(calibrator);

    auto context = engine.rootContext();
    context->setContextProperty("calibrator", &calibrator);

    return app.exec();
}
