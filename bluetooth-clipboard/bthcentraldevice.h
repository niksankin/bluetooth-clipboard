#ifndef BTHCENTRALDEVICE_H
#define BTHCENTRALDEVICE_H

#include <QObject>
#include <QHash>
#include <QJsonObject>
#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>

class BthCentralDevice: public QObject
{
    Q_OBJECT

public:
    BthCentralDevice();
    ~BthCentralDevice();

    void startScan();
    void endScan();

    void connectToDevice(const QBluetoothAddress& addr);
    void disconnectFromDevice(const QBluetoothAddress& addr);
    bool isDeviceConnected(const QBluetoothAddress& addr);

    void write(const QBluetoothAddress& addr, const QByteArray& data);

    // may be useless
    //QJsonObject getDeviceInfo(const QBluetoothAddress& addr);
    QByteArray getDevicePendingData(const QBluetoothAddress& addr);

signals:
    void deviceFound(QBluetoothAddress address);
    // TODO: maybe deviceDisappeared or smth
    //void deviceUpdated(QBluetoothAddress address);
    void deviceConnected(QBluetoothAddress address);
    void deviceDisconnected(QBluetoothAddress address);
    void dataReceived(QBluetoothAddress address, QByteArray data);
    void scanCancelled();
    void scanFinished();

private slots:
    void onDeviceFound();
    void onDeviceUpdated();
    void onReceiveDataReady();

private:
    QHash<QString, QBluetoothSocket*> clients;
    QBluetoothDeviceDiscoveryAgent* scanner = nullptr;
};

#endif // BTHCENTRALDEVICE_H
