#ifndef BTHPERIPHERALWIDGET_H
#define BTHPERIPHERALWIDGET_H

#include <QWidget>
#include "bthperipheraldevice.h"

namespace Ui {
class BthPeripheralWidget;
}

class BthPeripheralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BthPeripheralWidget(QWidget *parent = nullptr);
    ~BthPeripheralWidget();

signals:
    void deviceChanged(QBluetoothAddress address);
    void deviceDataReceived(QBluetoothAddress dataReceived, QByteArray data);
    void advertisingClicked(bool isActiveState);
    void emptyDeviceSelection();

public slots:
    void resetWidget();
    void deviceWriteData(QBluetoothAddress address, QByteArray data);

private:
    Ui::BthPeripheralWidget *ui;
    BthPeripheralDevice* peripheralBackend;
};

#endif // BTHPERIPHERALWIDGET_H
