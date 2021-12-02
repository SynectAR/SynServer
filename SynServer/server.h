#ifndef RPCSERVER_H
#define RPCSERVER_H

#include <QObject>

#include <grpcpp/grpcpp.h>

#include <vnarpc.grpc.pb.h>
#include <vnarpc.pb.h>

//service
using vnarpc::VnaRpc;

//messages
using vnarpc::EmptyMessage;
using vnarpc::PortCount;
using vnarpc::MeasureParams;
using vnarpc::PortStatus;
using vnarpc::PortsPair;
using vnarpc::Port;

//grpc status
using grpc::Status;

//grpc сервер и контекст сервера
using grpc::ServerContext;
using grpc::Server;


class VnaRpcServiceImpl final : public VnaRpc::Service
{
    Status getPortCount(ServerContext* context,
                        const EmptyMessage* request,
                        PortCount* reply) override;
    Status getPortStatus(ServerContext* context,
                        const Port* request,
                        PortStatus* reply) override;
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
};

class RpcServer : public QObject
{
    Q_OBJECT

public:
    explicit RpcServer(QObject *parent = nullptr);

private:
    VnaRpcServiceImpl service;
    std::shared_ptr<Server> server;
};

#endif // RPCSERVER_H
