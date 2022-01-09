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

Status VnaRpcServiceImpl::getPortStatus(ServerContext* context,
                                        const vnarpc::PortAndChannel* request,
                                        vnarpc::PortStatus* reply)
{
    auto port = calibrator->portStatus(request->channel(), request->port());
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
    int port = request->port();
    int channel = request->channel();

    std::string typeOfMeasure = request->type();
    QString deb;
    qDebug() << "type = " << deb.fromStdString(typeOfMeasure);

    switch (typeOfMeasure[0]) {
        case 'O':
            calibrator->measurePort(Measure::OPEN, channel, port);
            break;
        case 'S':
            calibrator->measurePort(Measure::SHORT, channel, port);
            break;
        case 'L':
            calibrator->measurePort(Measure::LOAD, channel, port);
            break;
        default:
            return Status::CANCELLED;
            break;
    }

    return Status::OK;
}

Status VnaRpcServiceImpl::measureThru(grpc::ServerContext *context,
                                            const vnarpc::ThruParams *request,
                                            vnarpc::EmptyMessage *reply)
{
    calibrator->measureThru(request->channel(), request->srcport(), request->rcvport());
    return Status::OK;
}

Status VnaRpcServiceImpl::apply(grpc::ServerContext *context,
                                      const vnarpc::Channel *request,
                                      vnarpc::EmptyMessage *reply)
{
    calibrator->apply(request->channel());
    return Status::OK;
}

Status VnaRpcServiceImpl::reset(grpc::ServerContext *context,
                                      const vnarpc::Channel *request,
                                      vnarpc::EmptyMessage *reply)
{
    calibrator->reset(request->channel());
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
                                    const vnarpc::Channel *request,
                                    vnarpc::SweepType *reply)
{
    SweepType vnaType = channelInfo->sweepType(request->channel());
    if (vnaType == SweepType::linear)
        reply->set_type(vnarpc::sweep_type::linear);
    else if (vnaType == SweepType::logarithmic)
        reply->set_type(vnarpc::sweep_type::logarithmic);
    else if (vnaType == SweepType::power)
        reply->set_type(vnarpc::sweep_type::power);
    else if (vnaType == SweepType::segment)
        reply->set_type(vnarpc::sweep_type::segment);
    return Status::OK;
}

Status VnaRpcServiceImpl::pointsCount(grpc::ServerContext *context,
                                      const vnarpc::Channel *request,
                                      vnarpc::Points *reply)
{
    reply->set_count(channelInfo->pointsCount(request->channel()));
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
                               const vnarpc::SweepTypeAndChannel *request,
                               vnarpc::Span *reply)
{
    int channel = request->channel();
    // span если измерение по мощности то по мощности иначе частота
    if (request->type() == vnarpc::sweep_type::power) {
        reply->set_max(channelInfo->maxPower(channel));
        reply->set_min(channelInfo->minPower(channel));
    } else {
        reply->set_max(channelInfo->maxFrequency(channel));
        reply->set_min(channelInfo->minFrequency(channel));
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

Status VnaRpcServiceImpl::calibrationType(grpc::ServerContext *context,
                                          const vnarpc::Channel *request,
                                          vnarpc::CalibrationType *reply)
{
    CalibrationType vnaCalType = channelInfo->calibrationType(request->channel());
    if (vnaCalType == CalibrationType::none)
        reply->set_type("none");
    else if (vnaCalType == CalibrationType::onePath)
        reply->set_type("onePath");
    else if (vnaCalType == CalibrationType::respO)
        reply->set_type("respO");
    else if (vnaCalType == CalibrationType::respS)
        reply->set_type("respS");
    else if (vnaCalType == CalibrationType::respT)
        reply->set_type("respT");
    else if (vnaCalType == CalibrationType::solt1)
        reply->set_type("solt1");
    else if (vnaCalType == CalibrationType::solt2)
        reply->set_type("solt2");
    return Status::OK;
}

Status VnaRpcServiceImpl::portList(grpc::ServerContext *context,
                                   const vnarpc::Channel *request,
                                   vnarpc::ActivePorts *reply)
{
    auto ports = channelInfo->listPorts(request->channel());
    for (auto p : ports)
        reply->add_ports(p - 1);
    return Status::OK;
}

Status VnaRpcServiceImpl::chooseSoltPorts(grpc::ServerContext *context,
                                           const vnarpc::SoltPorts *request,
                                           vnarpc::EmptyMessage *reply)
{
    QVector<int> ports;
    for (auto port : request->ports())
        ports.append(port);

    calibrator->soltCalibration(request->channel(), ports);
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

