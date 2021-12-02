#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>

#include <grpcpp/grpcpp.h>

#include "rpcclient.h"
#include "vnarpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using vnarpc::EmptyMessage;
using vnarpc::PortCount;
using vnarpc::MeasureParams;
using vnarpc::PortStatus;
using vnarpc::PortsPair;
using vnarpc::VnaRpc;

RpcClient::RpcClient(QObject* parent_)
    : QObject(parent_)
    , stub_(VnaRpc::NewStub(grpc::CreateChannel("192.168.1.85:50051",
                                 grpc::InsecureChannelCredentials()))) {}

int RpcClient::getPortCount()
{
    PortCount reply;
    ClientContext context;
    EmptyMessage request;
    Status status = stub_->getPortCount(&context, request, &reply);
    if (status.ok()) {
        return (int)reply.portcount();
    } else {
        qDebug() << (int)status.error_code();
        return -1;
    }
}
