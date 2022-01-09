#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>
#include <QPixmap>

#include <grpcpp/grpcpp.h>
#include "tempsoltcalibrator.h"
#include "rpcclient.h"
#include "vnarpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using vnarpc::EmptyMessage;
using vnarpc::PortCount;
using vnarpc::MeasureParams;
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

void RpcClient::listPort()
{
    EmptyMessage request;
    vnarpc::ActivePorts reply;
    ClientContext context;
    Status status = stub_->portList(&context, request, &reply);
    for (auto p : reply.ports())
        qDebug() << p;
    if (status.ok()) {
        qDebug() << "OK";
    } else {
        qDebug() << (int)status.error_code();
    }
}

void RpcClient::span()
{
    vnarpc::SweepType request;
    vnarpc::Span reply;
    ClientContext context;
    request.set_type(vnarpc::SweepType::power);
    Status status = stub_->span(&context, request, &reply);
    if (status.ok()) {
        qDebug() << "OK";
    } else {
        qDebug() << (int)status.error_code();
    }
}

void RpcClient::getPortStatus(int port)
{
    vnarpc::PortStatus reply;
    ClientContext context;
    vnarpc::Port request;
    request.set_port(port);
    Status status = stub_->getPortStatus(&context, request, &reply);

    qDebug() << "status port" << port <<
                "\nopen = " << reply.open() <<
                "\nshort = " << reply.short_() <<
                "\nload = " << reply.load();

    if (status.ok()) {
        qDebug() << "OK";
    } else {
        qDebug() << (int)status.error_code();
    }
}

void RpcClient::measurePort(std::string type, int port)
{
    EmptyMessage reply;
    ClientContext context;
    MeasureParams request;
    request.set_type(type);
    request.set_port(port);
    request.set_gender(1);
    Status status = stub_->measurePort(&context, request, &reply);
    if (status.ok()) {
        qDebug() << "OK";
    } else {
        qDebug() << "error code " << (int)status.error_code();
    }
}

void RpcClient::apply()
{
    EmptyMessage reply;
    ClientContext context;
    EmptyMessage request;
    Status status = stub_->apply(&context, request, &reply);
    if (status.ok()) {
        qDebug() << "OK";
    } else {
        qDebug() << (int)status.error_code();
    }
}
