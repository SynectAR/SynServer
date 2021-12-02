#include "server.h"

#include <vnarpc.grpc.pb.h>
#include <vnarpc.pb.h>

#include <QNetworkInterface>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>

using grpc::ServerBuilder;

Status VnaRpcServiceImpl::getPortCount(grpc::ServerContext *context,
                                             const vnarpc::EmptyMessage *request,
                                             vnarpc::PortCount *reply)
{
    //PortCount
    //int portcount
    reply->set_portcount(120);
    return Status::OK;
}

Status VnaRpcServiceImpl::getPortStatus(grpc::ServerContext *context,
                                              const vnarpc::Port *request,
                                              vnarpc::PortStatus *reply)
{
    //PortStatus
    //reply:
    //bool open
    //bool short
    //bool load
    //bool gender
    //request:
    //int port

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
    return Status::OK;
}

Status VnaRpcServiceImpl::measureThru(grpc::ServerContext *context,
                                            const vnarpc::PortsPair *request,
                                            vnarpc::EmptyMessage *reply)
{
    //PortsPair
    //firstport
    //secondport
    return Status::OK;
}

Status VnaRpcServiceImpl::apply(grpc::ServerContext *context,
                                      const vnarpc::EmptyMessage *request,
                                      vnarpc::EmptyMessage *reply)
{
    return Status::OK;
}

Status VnaRpcServiceImpl::reset(grpc::ServerContext *context,
                                      const vnarpc::EmptyMessage *request,
                                      vnarpc::EmptyMessage *reply)
{
    return Status::OK;
}

namespace {
    std::shared_ptr<Server> buildAndStartService(VnaRpcServiceImpl & service_)
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

RpcServer::RpcServer(QObject *parent)
  : QObject(parent)
  , server(buildAndStartService(this->service))
{
    QtConcurrent::run([=] {
        qDebug() << "RunServer() -> Thread: " << QThread::currentThreadId();

        this->server->Wait();
    });
}
