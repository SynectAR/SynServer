#include "server.h"

#include <QImage>
#include <QPixmap>
#include <vnarpc.grpc.pb.h>
#include <vnarpc.pb.h>

#include <QNetworkInterface>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>

using grpc::ServerBuilder;


VnaRpcServiceImpl::VnaRpcServiceImpl(ISoltCalibrator& calibrator, IChannelInfo& channelInfo)
    : calibrator(&calibrator),
      channelInfo(&channelInfo) {}

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
    reply->set_gender(port.gender == Gender::male ? 1 : 0);

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

Status VnaRpcServiceImpl::isConnected(grpc::ServerContext *context,
                                      const vnarpc::EmptyMessage *request,
                                      vnarpc::ConnectionState *reply)
{
    reply->set_connectionstate("Connected!");
    return Status::OK;
}

Status VnaRpcServiceImpl::isReady(grpc::ServerContext *context,
                                  const vnarpc::EmptyMessage *request,
                                  vnarpc::State *reply)
{
    //  вкл выкл
    reply->set_state(channelInfo->isReady());
    return Status::OK;
}

Status VnaRpcServiceImpl::sweepType(grpc::ServerContext *context,
                                    const vnarpc::EmptyMessage *request,
                                    vnarpc::SweepType *reply)
{
    SweepType vnaType = channelInfo->sweepType();
    if (vnaType == SweepType::linear)
        reply->set_type(vnarpc::SweepType::linear);
    else if (vnaType == SweepType::logarithmic)
        reply->set_type(vnarpc::SweepType::logarithmic);
    else if (vnaType == SweepType::power)
        reply->set_type(vnarpc::SweepType::power);
    else if (vnaType == SweepType::segment)
        reply->set_type(vnarpc::SweepType::segment);
    return Status::OK;
}

Status VnaRpcServiceImpl::pointsCount(grpc::ServerContext *context,
                                      const vnarpc::EmptyMessage *request,
                                      vnarpc::Points *reply)
{
    reply->set_count(channelInfo->pointsCount());
    return Status::OK;
}

Status VnaRpcServiceImpl::triggerMode(grpc::ServerContext *context,
                                      const vnarpc::EmptyMessage *request,
                                      vnarpc::TriggerMode *reply)
{
    TriggerMode vnaTrig = channelInfo->triggerMode();
    if (vnaTrig == TriggerMode::continuous)
        reply->set_triggermode(vnarpc::TriggerMode::continuous);
    else if (vnaTrig == TriggerMode::hold)
        reply->set_triggermode(vnarpc::TriggerMode::hold);
    return Status::OK;
}

Status VnaRpcServiceImpl::span(grpc::ServerContext *context,
                               const vnarpc::SweepType *request,
                               vnarpc::Span *reply)
{
    // span если измерение по мощности то по мощности иначе частота
    if (request->type() == vnarpc::SweepType::power) {
        reply->set_max(channelInfo->maxPower());
        reply->set_min(channelInfo->minPower());
    } else {
        reply->set_max(channelInfo->maxFrequency());
        reply->set_min(channelInfo->minFrequency());
    }
    return Status::OK;
}

Status VnaRpcServiceImpl::rfOut(grpc::ServerContext *context,
                                const vnarpc::EmptyMessage *request,
                                vnarpc::State *reply)
{
    reply->set_state(channelInfo->rfOut());
    return Status::OK;
}

RpcServer::RpcServer(ISoltCalibrator& calibrator, IChannelInfo& channelInfo, QObject *parent)
  : QObject(parent)
{
    service = new VnaRpcServiceImpl(calibrator, channelInfo);
    server = buildAndStartService(*service);
    QtConcurrent::run([=] {
        qDebug() << "RunServer() -> Thread: " << QThread::currentThreadId();

        this->server->Wait();
    });
}

std::shared_ptr<Server> RpcServer::buildAndStartService(VnaRpcServiceImpl& service_)
{
    for (auto &address : QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost) {
            _serverAddress = address.toString();
        }
    }
    _serverAddress += ":50051";
    qDebug() << _serverAddress;
    return ServerBuilder()
        .AddListeningPort(_serverAddress.toStdString(), grpc::InsecureServerCredentials())
        .RegisterService(&service_)
        .BuildAndStart();
}

QString RpcServer::getServerAddress() const
{
    return _serverAddress;
}

RpcServer::~RpcServer()
{
    delete service;
}

