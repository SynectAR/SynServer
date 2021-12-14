#include "server.h"

#include <vnarpc.grpc.pb.h>
#include <vnarpc.pb.h>

#include <QNetworkInterface>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>

using grpc::ServerBuilder;


VnaRpcServiceImpl::VnaRpcServiceImpl(ISoltCalibrator& calibrator) : calibrator(&calibrator) {}

Status VnaRpcServiceImpl::getPortCount(grpc::ServerContext *context,
                                             const vnarpc::EmptyMessage *request,
                                             vnarpc::PortCount *reply)
{
    //PortCount
    //int portcount
    reply->set_portcount(calibrator->portCount());
    return Status::OK;
}

Status VnaRpcServiceImpl::getPortStatus(grpc::ServerContext *context,
                                              const vnarpc::Port *request,
                                              vnarpc::PortStatus *reply)
{
    //getPortStatus

    //PortStatus
    //reply:
    //bool open
    //bool short
    //bool load
    //bool gender
    //request:
    //int port

    auto port = calibrator->portStatus(request->port());
    reply->set_open(port.OPEN);
    reply->set_short_(port.SHORT);
    reply->set_load(port.LOAD);
    reply->set_gender(port.gender == Gender::MALE ? 1 : 0);

    return Status::OK;
}

Status VnaRpcServiceImpl::measurePort(grpc::ServerContext *context,
                                            const vnarpc::MeasureParams *request,
                                            vnarpc::EmptyMessage *reply)
{
    //MeasureParams
    //int32 port
    //string type
    //bool gender

    int port = request->port();

    std::string typeOfMeasure = request->type();
    QString deb;
    qDebug() << "type = " << deb.fromStdString(typeOfMeasure);

    switch (typeOfMeasure[0]) {
        case 'O':
            calibrator->measurePort(Measure::OPEN, port);
            break;
        case 'S':
            calibrator->measurePort(Measure::SHORT, port);
            break;
        case 'L':
            calibrator->measurePort(Measure::LOAD, port);
            break;
        default:
            return Status::CANCELLED;
            break;
    }

    return Status::OK;
}

Status VnaRpcServiceImpl::measureThru(grpc::ServerContext *context,
                                            const vnarpc::PortsPair *request,
                                            vnarpc::EmptyMessage *reply)
{
    //PortsPair
    //firstport
    //secondport

    calibrator->measureThru(request->firstport(), request->secondport());
    return Status::OK;
}

Status VnaRpcServiceImpl::apply(grpc::ServerContext *context,
                                      const vnarpc::EmptyMessage *request,
                                      vnarpc::EmptyMessage *reply)
{
    calibrator->apply();
    return Status::OK;
}

Status VnaRpcServiceImpl::reset(grpc::ServerContext *context,
                                      const vnarpc::EmptyMessage *request,
                                      vnarpc::EmptyMessage *reply)
{
    calibrator->reset();
    return Status::OK;
}

namespace {
    std::shared_ptr<Server> buildAndStartService(VnaRpcServiceImpl& service_)
    {
        QString serverAddress;
        for (auto &address : QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost) {
                serverAddress = address.toString();
            }
        }
        serverAddress += ":50051";
        qDebug() << serverAddress;
        return ServerBuilder()
            .AddListeningPort(serverAddress.toStdString(), grpc::InsecureServerCredentials())
            .RegisterService(&service_)
            .BuildAndStart();
    }
}


RpcServer::RpcServer(ISoltCalibrator& calibrator, QObject *parent)
  : QObject(parent)
{
    service = new VnaRpcServiceImpl(calibrator);
    server = buildAndStartService(*service);
    QtConcurrent::run([=] {
        qDebug() << "RunServer() -> Thread: " << QThread::currentThreadId();

        this->server->Wait();
    });
}

RpcServer::~RpcServer()
{
    delete service;
}
