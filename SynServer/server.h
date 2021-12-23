#ifndef RPCSERVER_H
#define RPCSERVER_H

#include <QObject>

#include <grpcpp/grpcpp.h>

#include <vnarpc.grpc.pb.h>
#include <vnarpc.pb.h>

#include "isoltcalibrator.h"
#include "ichannelinfo.h"

//service
using vnarpc::VnaRpc;

//messages
using vnarpc::EmptyMessage;
using vnarpc::PortCount;
using vnarpc::MeasureParams;
using vnarpc::PortsPair;
using vnarpc::Port;
using vnarpc::State;
using vnarpc::ConnectionState;

//grpc status
using grpc::Status;

//grpc сервер и контекст сервера
using grpc::ServerContext;
using grpc::Server;
using grpc::ServerWriter;


class VnaRpcServiceImpl final : public VnaRpc::Service
{
public:
    VnaRpcServiceImpl(ISoltCalibrator& calibrator, IChannelInfo& channelInfo);

private:
    ISoltCalibrator* calibrator;
    IChannelInfo* channelInfo;

    // калибровка
    Status getPortCount(ServerContext* context,
                        const EmptyMessage* request,
                        PortCount* reply) override;
    Status getPortStatus(ServerContext* context,
                        const Port* request,
                        vnarpc::PortStatus* reply) override;
    Status measurePort(ServerContext* context,
                        const MeasureParams* request,
                        EmptyMessage* reply) override;
    Status measureThru(ServerContext* context,
                        const PortsPair* request,
                        EmptyMessage* reply) override;
    Status apply(ServerContext* context,
                        const EmptyMessage* request,
                        EmptyMessage* reply) override;
    Status reset(ServerContext* context,
                        const EmptyMessage* request,
                        EmptyMessage* reply) override;

    // статус
    Status isConnected(ServerContext* context,
                       const EmptyMessage* request,
                       ConnectionState* reply) override;
    Status isReady(ServerContext* context,
                   const EmptyMessage* request,
                   State* reply) override;
    Status sweepType(ServerContext* context,
                     const EmptyMessage* request,
                     vnarpc::SweepType* reply) override;
    Status pointsCount(ServerContext* context,
                       const EmptyMessage* request,
                       vnarpc::Points* reply) override;
    Status triggerMode(ServerContext* context,
                       const EmptyMessage* request,
                       vnarpc::TriggerMode* reply) override;
    Status span(ServerContext* context,
                const vnarpc::SweepType* request,
                vnarpc::Span* reply) override;
    Status rfOut(ServerContext* context,
                 const EmptyMessage* request,
                 vnarpc::State* reply) override;
    Status calibrationType(ServerContext* context,
                           const EmptyMessage* request,
                           vnarpc::CalibrationType* reply) override;

};

class RpcServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serverAddress READ getServerAddress NOTIFY serverAddressChanged)

public:
    RpcServer(ISoltCalibrator& calibrator, IChannelInfo& channelInfo, QObject *parent = nullptr);
    ~RpcServer();
    QString getServerAddress() const;

private:
    QString _serverAddress;
    VnaRpcServiceImpl* service;
    std::shared_ptr<Server> server;
    std::shared_ptr<Server> buildAndStartService(VnaRpcServiceImpl &service_);

signals:
    void serverAddressChanged(QString serverAddress);
};

#endif // RPCSERVER_H
