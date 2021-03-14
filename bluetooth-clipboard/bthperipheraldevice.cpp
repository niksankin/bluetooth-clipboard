#include "bthperipheraldevice.h"

BthPeripheralDevice::BthPeripheralDevice()
{
    server = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
}

BthPeripheralDevice::~BthPeripheralDevice(){
    delete server;
}

void BthPeripheralDevice::startServer(){

}

void BthPeripheralDevice::endServer(){

}

void BthPeripheralDevice::write(const QBluetoothAddress& addr, const QByteArray& data){

}

void BthPeripheralDevice::disconnectFromDevice(const QBluetoothAddress& addr){

}

/*QJsonObject BthPeripheralDevice::getDeviceInfo(const QBluetoothAddress& addr){
    return QJsonObject();
}*/

QByteArray BthPeripheralDevice::getDevicePendingData(const QBluetoothAddress& addr){
    return QByteArray();
}
