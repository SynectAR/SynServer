#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include <QObject>

#include <QImage>
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
using vnarpc::VnaRpc;


class RpcClient : public QObject
{
Q_OBJECT

public:
    RpcClient(QObject* parent_ = nullptr);
    int getPortCount();
    void measurePort(std::string type, int port);
    void apply();
    std::unique_ptr<VnaRpc::Stub> stub_;
    void getPortStatus(int port);
    QPixmap vnaQR();
    void span();
    void listPort(int channel);
};

#endif // RPCCLIENT_H

