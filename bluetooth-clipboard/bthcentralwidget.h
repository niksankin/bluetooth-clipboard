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
    void deviceChanged(const QString address);
    void deviceDataReceived(const QString address, QByteArray data);
    void scanClicked(bool isActiveState);
    void emptyDeviceSelection();

public slots:
    void resetWidget();
    void deviceWriteData(const QString address, QByteArray data);

private:
    Ui::BthCentralWidget *ui;

    BthCentralDevice* centralBackend;
};

#endif // QCENTRALWIDGET_H
