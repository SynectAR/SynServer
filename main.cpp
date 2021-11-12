#include "scpisession.h"
#include "scpisession.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QQmlContext>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    ScpiSession client;
    client.connectedToHost();

    auto context = engine.rootContext();
    context->setContextProperty("tcpClient", &client);

   /* QObject::connect(&client, &TcpClient::nameChanged,
                     [&engine](const QString& name)
    {
        auto* root = engine.rootObjects().first();
        QQmlProperty nameProperty(root, "name");
        nameProperty.write(name);
    });*/
    client.getId();

    return app.exec();
}
