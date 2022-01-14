#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>
#include <QNetworkInterface>
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
using vnarpc::VnaRpc;

RpcClient::RpcClient(QObject* parent_)
    : QObject(parent_) {

    QString _serverAddress;
    for (auto &address : QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost) {
            _serverAddress = address.toString();
        }
    }
    _serverAddress += ":50051";
    stub_ = VnaRpc::NewStub(grpc::CreateChannel(_serverAddress.toStdString(),
                                                grpc::InsecureChannelCredentials()));
}

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

void RpcClient::listPort(int channel)
{
    vnarpc::Channel request;
    vnarpc::ActivePorts reply;
    ClientContext context;
    request.set_channel(channel);
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
    vnarpc::SweepTypeAndChannel request;
    vnarpc::Span reply;
    ClientContext context;
    request.set_channel(1);
    request.set_type(vnarpc::sweep_type::power);
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
    vnarpc::PortAndChannel request;
    request.set_channel(1);
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
    request.set_channel(1);
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
    vnarpc::Channel request;
    request.set_channel(1);
    Status status = stub_->apply(&context, request, &reply);
    if (status.ok()) {
        qDebug() << "OK";
    } else {
        qDebug() << (int)status.error_code();
    }
}
