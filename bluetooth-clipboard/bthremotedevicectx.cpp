#include "bthremotedevicectx.h"

BthRemoteDeviceCtx::BthRemoteDeviceCtx(QObject *parent) : QObject(parent)
{
    resetDevice();
}

BthRemoteDeviceCtx::BthRemoteDeviceCtx(QBluetoothSocket* socket, QObject *parent) : QObject(parent){
    setSocket(socket);
}

BthRemoteDeviceCtx::~BthRemoteDeviceCtx(){
    delete socket;
}

void BthRemoteDeviceCtx::connectToDevice(const QBluetoothAddress& address, const QBluetoothUuid& service){
    // already connected, need to be disconnected first
    if(socket->state() != QBluetoothSocket::UnconnectedState)
        return;

    socket->connectToService(address, service);

    this->address = address;
    this->service = service;
}

void BthRemoteDeviceCtx::disconnectFromDevice(){
    socket->disconnectFromService();
}

QBluetoothAddress BthRemoteDeviceCtx::getPeerAddress(){
    return address;
}

QBluetoothUuid BthRemoteDeviceCtx::getPeerService(){
    return service;
}

qint64 BthRemoteDeviceCtx::writeData(const QByteArray &byteArray){
    return socket->write(byteArray);
}

QByteArray BthRemoteDeviceCtx::readData(qint64 maxSize){
    return socket->read(maxSize);
}

void BthRemoteDeviceCtx::setSocket(QBluetoothSocket* socket){

    this->socket = socket;

    // already connected socket, given from server
    if(!socket->peerAddress().isNull())
        this->address = socket->peerAddress();

    connect(this->socket, &QBluetoothSocket::readyRead, this, [this](){
        emit readyRead();
    });

    connect(this->socket, &QBluetoothSocket::connected, this, [this](){
        emit connected();
    });

    connect(this->socket, &QBluetoothSocket::disconnected, this, [this](){
        emit disconnected();
    });
}

void BthRemoteDeviceCtx::resetDevice(){
    delete socket;
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    service = QBluetoothUuid();
    address = QBluetoothAddress();
}

QBluetoothSocket::SocketState BthRemoteDeviceCtx::getSocketState(){
    return socket->state();
}
