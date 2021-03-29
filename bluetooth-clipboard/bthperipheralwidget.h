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
    void deviceChanged(const QString name);
    void deviceDataReceived(const QString name, QByteArray data);
    void advertisingClicked(bool isActiveState);
    void emptyDeviceSelection();

public slots:
    void resetWidget();
    void deviceWriteData(const QString name, QByteArray data);

private:
    Ui::BthPeripheralWidget *ui;
    BthPeripheralDevice* peripheralBackend;
};

#endif // BTHPERIPHERALWIDGET_H
