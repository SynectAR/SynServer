#include "scpisoltcalibrator.h"
#include "server.h"
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


static std::string toSvgString(const qrcodegen::QrCode &qr, int border) {
    if (border < 0)
        throw std::domain_error("Border must be non-negative");
    if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
        throw std::overflow_error("Border too large");

    std::ostringstream sb;
    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
    sb << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"#000000\"/>\n";
    sb << "</svg>\n";
    return sb.str();
}
using namespace std;


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    ScpiSoltCalibrator calibrator;
    auto number = calibrator.deviceInfo();

    QByteArray ba = number.toLocal8Bit();
    const char* QR_text = ba.data();

    auto qr = qrcodegen::QrCode::encodeText(QR_text, qrcodegen::QrCode::Ecc::QUARTILE);
    //auto qr = qrcodegen::QrCode::encodeText("Laufer Artyom1", qrcodegen::QrCode::Ecc::QUARTILE);
    cout << toSvgString(qr, 4) << endl;
    auto string = toSvgString(qr, 4);

    ofstream outStream("C:/Users/79234/Desktop/SynServer/SynServer/SynServer/svg_xml.svg");
    outStream << string;
    outStream.close();

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

    //ScpiSoltCalibrator calibrator;
    QObject::connect(&server, &MyTcpServer::peerConnected,
                     &server, [&server, &calibrator] () {
        server.sendMessage(calibrator.deviceInfo());
    });

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
