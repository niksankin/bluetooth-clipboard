#ifndef QCENTRALWIDGET_H
#define QCENTRALWIDGET_H

#include <QWidget>
#include <QtBluetooth/QBluetoothAddress>
#include "bthcentraldevice.h"

namespace Ui {
class BthCentralWidget;
}

class BthCentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BthCentralWidget(QWidget *parent = nullptr);
    ~BthCentralWidget();

signals:
    void deviceChanged(QBluetoothAddress address);
    void deviceDataReceived(QBluetoothAddress dataReceived, QByteArray data);
    void scanClicked(bool isActiveState);
    void emptyDeviceSelection();

public slots:
    void resetWidget();
    void deviceWriteData(QBluetoothAddress address, QByteArray data);

private:
    Ui::BthCentralWidget *ui;

    BthCentralDevice* centralBackend;
};

#endif // QCENTRALWIDGET_H
