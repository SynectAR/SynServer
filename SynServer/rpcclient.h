#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include <QObject>

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "vnarpc.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using vnarpc::EmptyMessage;
using vnarpc::PortCount;
using vnarpc::MeasureParams;
using vnarpc::PortStatus;
using vnarpc::PortsPair;
using vnarpc::VnaRpc;


class RpcClient : public QObject
{
Q_OBJECT

public:
    RpcClient(QObject* parent_ = nullptr);
    int getPortCount();
    std::unique_ptr<VnaRpc::Stub> stub_;
};

#endif // RPCCLIENT_H

