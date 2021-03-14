#ifndef BTHCLIPBOARDWIDGET_H
#define BTHCLIPBOARDWIDGET_H

#include <QWidget>
#include <QClipboard>
#include <QtBluetooth/QBluetoothAddress>
#include <QListWidget>

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
    void writeDeviceData(QBluetoothAddress address, QByteArray data);

public slots:
    void onDeviceDataReceived(QBluetoothAddress address, QByteArray data);
    void onDeviceChanged(QBluetoothAddress address);
    void onAbsentDevice();

private:
    Ui::BthClipboardWidget *ui;

    QClipboard* clipboardBackend = nullptr;
    QBluetoothAddress currentDevice;
};

#endif // BTHCLIPBOARDWIDGET_H
