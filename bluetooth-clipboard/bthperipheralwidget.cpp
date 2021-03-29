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

        peripheralBackend->disconnectFromDevice(currentDevice->text());
    });

    connect(ui->clientDevices, &QListWidget::currentItemChanged, this, [this](QListWidgetItem *current, QListWidgetItem *previous){
        ui->connectionControl->setEnabled(true);

        emit deviceChanged(current->text(), true);
    });

    connect(peripheralBackend, &BthPeripheralDevice::deviceConnected, this, [this](const QString& name){
        ui->clientDevices->addItem(name);

        emit deviceConnected(name);
    });

    connect(peripheralBackend, &BthPeripheralDevice::deviceDisconnected, this, [this](const QString& name){
        auto foundItem = ui->clientDevices->findItems(name, Qt::MatchFixedString);

        // only single row may exist for specific bluetooth device address
        ui->clientDevices->blockSignals(true);
        QListWidgetItem* item = ui->clientDevices->takeItem(0);
        ui->clientDevices->blockSignals(false);

        delete item;

        if(!ui->clientDevices->count()){
            resetWidget();

            emit emptyDeviceSelection();
        }
        else
            emit deviceDisconnected(name);
    });

    connect(peripheralBackend, &BthPeripheralDevice::dataReceived, this, [this](const QString& name, QByteArray data){
        emit deviceDataReceived(name, data);
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

void BthPeripheralWidget::deviceWriteData(const QString name, QByteArray data){
    peripheralBackend->write(name, data);
}
