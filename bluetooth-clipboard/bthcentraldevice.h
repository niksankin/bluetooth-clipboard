#ifndef BTHCENTRALDEVICE_H
#define BTHCENTRALDEVICE_H

#include <QObject>
#include <QHash>
#include <QJsonObject>
#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>

#include "bthremotedevicectx.h"

class BthCentralDevice: public QObject
{
    Q_OBJECT

public:
    explicit BthCentralDevice(QObject *parent = nullptr);
    ~BthCentralDevice();

    void startScan();
    void endScan();

    void connectToDevice(const QBluetoothAddress& addr);
    void disconnectFromDevice(const QBluetoothAddress& addr);
    bool isDeviceConnected(const QBluetoothAddress& addr);

    void write(const QBluetoothAddress& addr, const QByteArray& data);

signals:
    void deviceFound(QBluetoothAddress address);
    void deviceConnected(QBluetoothAddress address);
    void deviceDisconnected(QBluetoothAddress address);
    void connectionError(QString what);
    void dataReceived(QBluetoothAddress address, QByteArray data);
    void scanFinished();

private slots:
    void onDeviceFound(const QBluetoothDeviceInfo& deviceInfo);
    void onReceiveDataReady();

private:
    QHash<QString, BthRemoteDeviceCtx*> clientsCtx;
    QBluetoothDeviceDiscoveryAgent* deviceScanner = nullptr;

    void resetScanner();
};

#endif // BTHCENTRALDEVICE_H
