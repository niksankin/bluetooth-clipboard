#include "bthcentraldevice.h"

BthCentralDevice::BthCentralDevice(QObject *parent)
    :QObject(parent)
{
    scanner = new QBluetoothDeviceDiscoveryAgent(this);
}

BthCentralDevice::~BthCentralDevice()
{
    delete scanner;
}

void BthCentralDevice::startScan()
{

}

void BthCentralDevice::endScan()
{

}

void BthCentralDevice::connectToDevice(const QBluetoothAddress& addr){

}

void BthCentralDevice::disconnectFromDevice(const QBluetoothAddress& addr){

}

bool BthCentralDevice::isDeviceConnected(const QBluetoothAddress& addr){
    return false;
}

void BthCentralDevice::write(const QBluetoothAddress& addr, const QByteArray& data){

}

/*QJsonObject BthCentralDevice::getDeviceInfo(const QBluetoothAddress& addr)
{
    return QJsonObject();
}*/

QByteArray BthCentralDevice::getDevicePendingData(const QBluetoothAddress& addr)
{
    return QByteArray();
}

void BthCentralDevice::onDeviceFound(){

}

void BthCentralDevice::onDeviceUpdated(){

}

void BthCentralDevice::onReceiveDataReady(){

}
