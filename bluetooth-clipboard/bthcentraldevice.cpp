#include "bthcentraldevice.h"

#include <QtEndian>
#include <QBuffer>
#include <QDataStream>

#include "constants.h"

BthCentralDevice::BthCentralDevice(QObject *parent)
    :QObject(parent)
{
    resetScanner();
}

BthCentralDevice::~BthCentralDevice()
{
    for(auto i : clientsCtx)
        delete i;

    delete deviceScanner;
}

void BthCentralDevice::startScan()
{
    deviceScanner->start();
}

void BthCentralDevice::endScan()
{
    deviceScanner->stop();

    resetScanner();
}

void BthCentralDevice::resetScanner(){
    if(deviceScanner != nullptr)
        delete deviceScanner;

    deviceScanner = new QBluetoothDeviceDiscoveryAgent(this);

    connect(deviceScanner, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BthCentralDevice::onDeviceFound);
    connect(deviceScanner, &QBluetoothDeviceDiscoveryAgent::finished, this, &BthCentralDevice::scanFinished);
    connect(deviceScanner, &QBluetoothDeviceDiscoveryAgent::canceled, this, &BthCentralDevice::scanFinished);
}

void BthCentralDevice::connectToDevice(const QBluetoothAddress& addr){
    clientsCtx[addr.toString()]->connectToDevice(addr, serviceUuid);
}

void BthCentralDevice::disconnectFromDevice(const QBluetoothAddress& addr){
    clientsCtx[addr.toString()]->disconnectFromDevice();
}

bool BthCentralDevice::isDeviceConnected(const QBluetoothAddress& addr){
    return clientsCtx[addr.toString()]->getSocketState() == QBluetoothSocket::SocketState::ConnectedState;
}

void BthCentralDevice::onDeviceFound(const QBluetoothDeviceInfo& deviceInfo){
    QBluetoothAddress addr = deviceInfo.address();

    BthRemoteDeviceCtx* ctx = new BthRemoteDeviceCtx();

    clientsCtx.insert(addr.toString(), ctx);

    connect(clientsCtx[addr.toString()], &BthRemoteDeviceCtx::readyRead, this, &BthCentralDevice::onReceiveDataReady);
    connect(clientsCtx[addr.toString()], &BthRemoteDeviceCtx::connected, this, [this](){
        BthRemoteDeviceCtx* ctx = static_cast<BthRemoteDeviceCtx*>(sender());

        emit deviceConnected(ctx->getPeerAddress());
    });
    connect(clientsCtx[addr.toString()], &BthRemoteDeviceCtx::disconnected, this, [this](){
        BthRemoteDeviceCtx* ctx = static_cast<BthRemoteDeviceCtx*>(sender());

        emit deviceDisconnected(ctx->getPeerAddress());
    });
    connect(clientsCtx[addr.toString()], &BthRemoteDeviceCtx::error, this, [this](QBluetoothSocket::SocketError error){
        BthRemoteDeviceCtx* ctx = static_cast<BthRemoteDeviceCtx*>(sender());

        emit connectionError(ctx->getSocketErrorString());
    });

    emit deviceFound(addr);
}

void BthCentralDevice::onReceiveDataReady(){
    BthRemoteDeviceCtx* ctx = static_cast<BthRemoteDeviceCtx*>(sender());

    QByteArray data = ctx->readData();

    emit dataReceived(ctx->getPeerAddress(), data);
}

void BthCentralDevice::write(const QBluetoothAddress& addr, const QByteArray& data){
    clientsCtx[addr.toString()]->writeData(data);
}
