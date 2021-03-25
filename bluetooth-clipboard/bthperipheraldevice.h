#ifndef BTHPERIPHERALDEVICE_H
#define BTHPERIPHERALDEVICE_H

#include <QObject>
#include <QByteArray>
#include <QJsonObject>
#include <QHash>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothServer>
#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothHostInfo>

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

private slots:
    void onNewConnection();

private:
    QHash<QString, QBluetoothSocket*> clients;
    QBluetoothServer* server = nullptr;
    QBluetoothServiceInfo serviceInfo;

    QList<QBluetoothHostInfo> localAdapters;
    QBluetoothSocket* sock = nullptr;
};

#endif // BTHPERIPHERALDEVICE_H
