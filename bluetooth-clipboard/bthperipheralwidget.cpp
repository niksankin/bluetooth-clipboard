#include "bthperipheralwidget.h"
#include "ui_bthperipheralwidget.h"

const QString startAdvertisingStr = "Start\nadvertising";
const QString stopAdvertisingStr = "Stop\nadvertising";
const QString disconnectStr = "Disconnect";

Q_GLOBAL_STATIC(BthPeripheralDevice, peripheralDevice)

BthPeripheralWidget::BthPeripheralWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BthPeripheralWidget)
{
    ui->setupUi(this);

    resetWidget();

    ui->advertisingControl->setText(startAdvertisingStr);

    peripheralBackend = peripheralDevice;

    // TODO: maybe disconnect all clients when server off
    connect(ui->advertisingControl, &QPushButton::clicked, this, [this](bool checked){
        if(ui->advertisingControl->text() == startAdvertisingStr){
            ui->advertisingControl->setText(stopAdvertisingStr);

            emit advertisingClicked(true);

            peripheralBackend->startServer();
        }
        else{
            ui->advertisingControl->setText(startAdvertisingStr);

            peripheralBackend->endServer();

            emit advertisingClicked(false);
        }
    });

    connect(ui->connectionControl, &QPushButton::clicked, this, [this](bool checked){
        auto currentDevice = ui->clientDevices->currentItem();

        peripheralBackend->disconnectFromDevice(QBluetoothAddress(currentDevice->text()));
    });

    connect(ui->clientDevices, &QListWidget::currentItemChanged, this, [this](QListWidgetItem *current, QListWidgetItem *previous){
        if(current != nullptr){
            ui->connectionControl->setEnabled(true);

            emit deviceChanged(QBluetoothAddress(current->text()));
        }
        else{
            resetWidget();

            emit emptyDeviceSelection();
        }
    });

    connect(peripheralBackend, &BthPeripheralDevice::deviceConnected, this, [this](QBluetoothAddress address){
        ui->clientDevices->addItem(address.toString());
    });

    connect(peripheralBackend, &BthPeripheralDevice::deviceDisconnected, this, [this](QBluetoothAddress address){
        auto foundItem = ui->clientDevices->findItems(address.toString(), Qt::MatchFixedString);

        // only single row may exist for specific bluetooth device address
        ui->clientDevices->removeItemWidget(foundItem.at(0));

        if(!ui->clientDevices->count())
            ui->connectionControl->setEnabled(false);
    });

    connect(peripheralBackend, &BthPeripheralDevice::dataReceived, this, [this](QBluetoothAddress address, QByteArray data){
        emit deviceDataReceived(address, data);
    });
}

BthPeripheralWidget::~BthPeripheralWidget()
{
    delete ui;
}

void BthPeripheralWidget::resetWidget(){
    ui->clientDevices->clear();

    ui->connectionControl->setText(disconnectStr);
    ui->connectionControl->setEnabled(false);
}

void BthPeripheralWidget::deviceWriteData(QBluetoothAddress address, QByteArray data){
    peripheralBackend->write(address, data);
}
