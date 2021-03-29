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

#include "bthremotedevicectx.h"

class BthPeripheralDevice: public QObject
{
    Q_OBJECT

public:
    explicit BthPeripheralDevice(QObject *parent = nullptr);
    ~BthPeripheralDevice();

    void startServer();
    void endServer();

    void disconnectFromDevice(const QString name);
    void write(const QString name, const QByteArray data);

signals:
    void deviceConnected(const QString name);
    void deviceDisconnected(const QString name);
    void connectionError(QString what);
    void dataReceived(const QString name, QByteArray data);

private slots:
    void onDeviceConnected();
    void onReceiveDataReady();

private:
    QHash<QString, BthRemoteDeviceCtx*> clientsCtx;
    QBluetoothServer* server = nullptr;
    QBluetoothServiceInfo serviceInfo;
};

#endif // BTHPERIPHERALDEVICE_H
