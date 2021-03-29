#include "bthperipheraldevice.h"

#include "constants.h"

#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtEndian>
#include <QBuffer>
#include <QDataStream>

BthPeripheralDevice::BthPeripheralDevice(QObject *parent)
    :QObject(parent)
{
    server = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(server, &QBluetoothServer::newConnection, this, &BthPeripheralDevice::onDeviceConnected);
}

BthPeripheralDevice::~BthPeripheralDevice(){
    serviceInfo.unregisterService();

    for(auto i : clientsCtx)
        delete i;

    delete server;
}

void BthPeripheralDevice::startServer(){
    server->listen();

    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("Bluetooth Clipboard Server"));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
                             tr("Bluetooth clipboard syncronization tool"));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("HSE"));

    serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));

    QBluetoothServiceInfo::Sequence publicBrowse;
    publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
    serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList,
                             publicBrowse);

    QBluetoothServiceInfo::Sequence protocolDescriptorList;
    QBluetoothServiceInfo::Sequence protocol;

    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
             << QVariant::fromValue(quint8(server->serverPort()));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                             protocolDescriptorList);

    serviceInfo.registerService();
}

void BthPeripheralDevice::endServer(){
    serviceInfo.unregisterService();
    server->close();
}

void BthPeripheralDevice::write(const QString name, const QByteArray data){
    QByteArray dataSize;
    QBuffer buf(&dataSize);
    buf.open(QBuffer::WriteOnly);

    qint64 size = data.size();

    QDataStream stream(&buf);
    stream << size;

    buf.close();

    clientsCtx[name]->writeData(dataSize);
    clientsCtx[name]->writeData(data);
}

void BthPeripheralDevice::disconnectFromDevice(const QString name){
    clientsCtx[name]->disconnectFromDevice();
}

void BthPeripheralDevice::onDeviceConnected(){
    QBluetoothSocket* socket = server->nextPendingConnection();

    BthRemoteDeviceCtx* ctx = new BthRemoteDeviceCtx(socket);

    clientsCtx.insert(ctx->getPeerName(), ctx);

    connect(clientsCtx[ctx->getPeerName()], &BthRemoteDeviceCtx::readyRead, this, &BthPeripheralDevice::onReceiveDataReady);
    connect(clientsCtx[ctx->getPeerName()], &BthRemoteDeviceCtx::connected, this, [this](){
        BthRemoteDeviceCtx* ctx = static_cast<BthRemoteDeviceCtx*>(sender());

        emit deviceConnected(ctx->getPeerName());
    });
    connect(clientsCtx[ctx->getPeerName()], &BthRemoteDeviceCtx::disconnected, this, [this](){
        BthRemoteDeviceCtx* ctx = static_cast<BthRemoteDeviceCtx*>(sender());

        emit deviceDisconnected(ctx->getPeerName());
    });
    connect(clientsCtx[ctx->getPeerName()], &BthRemoteDeviceCtx::error, this, [this](QBluetoothSocket::SocketError error){
        BthRemoteDeviceCtx* ctx = static_cast<BthRemoteDeviceCtx*>(sender());

        emit connectionError(ctx->getSocketErrorString());
    });

    emit deviceConnected(ctx->getPeerName());
}

void BthPeripheralDevice::onReceiveDataReady(){
    BthRemoteDeviceCtx* ctx = static_cast<BthRemoteDeviceCtx*>(sender());

    QByteArray data = ctx->readData(sizeof(qint64));
    qint64 dataLen;

    QBuffer buf(&data);
    buf.open(QBuffer::ReadOnly);

    QDataStream stream(&buf);
    stream >> dataLen;

    buf.close();

    data = ctx->readData(dataLen);

    emit dataReceived(ctx->getPeerName(), data);
}
