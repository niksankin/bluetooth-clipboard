#ifndef BTHPERIPHERALDEVICE_H
#define BTHPERIPHERALDEVICE_H

#include <QObject>
#include <QByteArray>
#include <QJsonObject>
#include <QHash>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothServer>
#include <QtBluetooth/QBluetoothAddress>

class BthPeripheralDevice: public QObject
{
    Q_OBJECT

public:
    explicit BthPeripheralDevice(QObject *parent = nullptr);
    ~BthPeripheralDevice();

    void startServer();
    void endServer();

    void disconnectFromDevice(const QBluetoothAddress& addr);
    void write(const QBluetoothAddress& addr, const QByteArray& data);

    // may be useless
    // QJsonObject getDeviceInfo(const QBluetoothAddress& addr);
    QByteArray getDevicePendingData(const QBluetoothAddress& addr);

signals:
    void deviceConnected(QBluetoothAddress address);
    void deviceDisconnected(QBluetoothAddress address);
    void dataReceived(QBluetoothAddress address, QByteArray data);

private:
    QHash<QString, QBluetoothSocket*> clients;
    QBluetoothServer* server = nullptr;
};

#endif // BTHPERIPHERALDEVICE_H
