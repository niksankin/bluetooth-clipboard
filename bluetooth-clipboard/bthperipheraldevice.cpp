#include "bthperipheraldevice.h"

#include "constants.h"

#include <QtBluetooth/QBluetoothLocalDevice>

BthPeripheralDevice::BthPeripheralDevice(QObject *parent)
    :QObject(parent)
{
    server = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(server, &QBluetoothServer::newConnection, this, &BthPeripheralDevice::onNewConnection);

    bool result = server->listen(QBluetoothAddress());

    QBluetoothServiceInfo::Sequence profileSequence;
    QBluetoothServiceInfo::Sequence classId;
    classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
    classId << QVariant::fromValue(quint16(0x100));
    profileSequence.append(QVariant::fromValue(classId));
    serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
                             profileSequence);

    classId.clear();
    classId << QVariant::fromValue(QBluetoothUuid(serviceUuid));
    classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));

    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);

    //! [Service name, description and provider]
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("Bt Chat Server"));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
                             tr("Example bluetooth chat server"));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("qt-project.org"));
    //! [Service name, description and provider]

    //! [Service UUID set]
    serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));
    //! [Service UUID set]

    //! [Service Discoverability]
    QBluetoothServiceInfo::Sequence publicBrowse;
    publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
    serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList,
                             publicBrowse);
    //! [Service Discoverability]

    //! [Protocol descriptor list]
    QBluetoothServiceInfo::Sequence protocolDescriptorList;
    QBluetoothServiceInfo::Sequence protocol;
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    protocol.clear();
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
             << QVariant::fromValue(quint8(server->serverPort()));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                             protocolDescriptorList);
    //! [Protocol descriptor list]

    //! [Register service]
    serviceInfo.registerService();
}

BthPeripheralDevice::~BthPeripheralDevice(){
    serviceInfo.unregisterService();

    delete sock;
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

QByteArray BthPeripheralDevice::getDevicePendingData(const QBluetoothAddress& addr){
    return QByteArray();
}

void BthPeripheralDevice::onNewConnection(){
    sock = server->nextPendingConnection();
}
