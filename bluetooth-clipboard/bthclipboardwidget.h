#ifndef BTHCLIPBOARDWIDGET_H
#define BTHCLIPBOARDWIDGET_H

#include <QWidget>
#include <QClipboard>
#include <QtBluetooth/QBluetoothAddress>
#include <QListWidget>

#include "bthclipboard.h"

namespace Ui {
class BthClipboardWidget;
}

class BthClipboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BthClipboardWidget(QWidget *parent = nullptr);
    ~BthClipboardWidget();

signals:
    void writeDeviceData(const QString id, QByteArray data);

public slots:
    void onDeviceDataReceived(const QString id, QByteArray data);
    void onDeviceChanged(const QString id, bool isConnected);
    void onDeviceConnected(const QString id);
    void onDeviceDisconnected(const QString id);
    void onAbsentDevice();

private:
    Ui::BthClipboardWidget *ui;

    BthClipboard* clipboardBackend = nullptr;
    QString currentDevice;
};

#endif // BTHCLIPBOARDWIDGET_H
