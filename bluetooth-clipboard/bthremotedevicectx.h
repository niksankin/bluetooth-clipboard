#ifndef BTHREMOTEDEVICECTX_H
#define BTHREMOTEDEVICECTX_H

#include <QObject>
#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QBluetoothDeviceInfo>

/*
Helper class for representing remote bluetooth devices.

BthRemoteDeviceCtx may be constructed from sockets of such types:
1) Sockets, obtained from QBluetoothServer
2) Sockets, dynamically allocated by user on heap

BthRemoteDeviceCtx class takes ownership of socket object.

Main purpose of this class is to give the access to Bluetooth
device address and service UUID in slot that processes disconnected()
signal. These values can not be obtained from QBluetoothSocket because:
1) There is no method for obtaining service UUID value from socket
2) Address of remote Bluetooth device is set to NULL before disconnected()
signal is emitted
*/
class BthRemoteDeviceCtx : public QObject
{
    Q_OBJECT
public:
    explicit BthRemoteDeviceCtx(QObject *parent = nullptr);
    BthRemoteDeviceCtx(QBluetoothSocket* socket, QObject *parent = nullptr);
    ~BthRemoteDeviceCtx();

    void connectToDevice(const QBluetoothAddress& address, const QBluetoothUuid& service);
    void disconnectFromDevice();

    QBluetoothAddress getPeerAddress();
    QBluetoothUuid getPeerService();
    QBluetoothSocket::SocketState getSocketState();

    void setSocket(QBluetoothSocket* socket);

    void resetDevice();

    qint64 writeData(const QByteArray &byteArray);
    QByteArray readData(qint64 maxSize);

signals:
    void connected();
    void disconnected();
    void readyRead();

private:
    QBluetoothSocket* socket = nullptr;
    QBluetoothUuid  service;
    QBluetoothAddress address;
};

#endif // BTHREMOTEDEVICECTX_H
