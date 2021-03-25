#include "bthcentralwidget.h"
#include "ui_bthcentralwidget.h"

const QString startScanStr = "Start\nscan";
const QString stopScanStr = "Stop\nscan";
const QString connectToDeviceStr = "Connect";
const QString disconnectDeviceStr = "Disconnect";

Q_GLOBAL_STATIC(BthCentralDevice, centralDevice)

BthCentralWidget::BthCentralWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BthCentralWidget)
{
    ui->setupUi(this);

    resetWidget();

    ui->scanControl->setText(startScanStr);

    centralBackend = centralDevice;

    connect(ui->scanControl, &QPushButton::clicked, this, [this](bool checked){
        if(ui->scanControl->text() == startScanStr){
            ui->scanControl->setText(stopScanStr);

            emit scanClicked(true);

            centralBackend->startScan();
        }
        else{
            ui->scanControl->setText(startScanStr);

            centralBackend->endScan();

            emit scanClicked(false);
        }
    });

    connect(centralBackend, &BthCentralDevice::scanFinished, this, [this](){
        ui->scanControl->setText(startScanStr);

        emit scanClicked(false);
    });

    connect(ui->connectionControl, &QPushButton::clicked, this, [this](bool checked){
        auto currentDevice = ui->foundDevices->currentItem();

        if(ui->connectionControl->text() == connectToDeviceStr){
            centralBackend->connectToDevice(QBluetoothAddress(currentDevice->text()));
        }
        else{
            centralBackend->disconnectFromDevice(QBluetoothAddress(currentDevice->text()));
        }
    });

    connect(ui->foundDevices, &QListWidget::currentItemChanged, this, [this](QListWidgetItem *current, QListWidgetItem *previous){
        if(current != nullptr){
            ui->connectionControl->setEnabled(true);

            bool isConnected = centralBackend->isDeviceConnected(QBluetoothAddress(current->text()));

            if(isConnected)
                ui->connectionControl->setText(disconnectDeviceStr);
            else
                ui->connectionControl->setText(connectToDeviceStr);

            emit deviceChanged(QBluetoothAddress(current->text()));
        }
        else{
            resetWidget();
            emit emptyDeviceSelection();
        }
    });

    connect(centralBackend, &BthCentralDevice::deviceFound, this, [this](QBluetoothAddress address){
        if(!ui->foundDevices->findItems(address.toString(), Qt::MatchFixedString).size())
            ui->foundDevices->addItem(address.toString());
    });

    connect(centralBackend, &BthCentralDevice::deviceConnected, this, [this](QBluetoothAddress address){
        auto currentDevice = ui->foundDevices->currentItem();

        if(currentDevice->text() == address.toString())
            ui->connectionControl->setText(disconnectDeviceStr);
    });

    connect(centralBackend, &BthCentralDevice::deviceDisconnected, this, [this](QBluetoothAddress address){
        auto currentDevice = ui->foundDevices->currentItem();
        QString kek = currentDevice->text();
        QString puk = address.toString();

        if(currentDevice->text() == address.toString())
            ui->connectionControl->setText(connectToDeviceStr);
    });

    connect(centralBackend, &BthCentralDevice::dataReceived, this, [this](QBluetoothAddress address, QByteArray data){
        emit deviceDataReceived(address, data);
    });
}

BthCentralWidget::~BthCentralWidget()
{
    delete ui;
}

void BthCentralWidget::resetWidget(){
    ui->foundDevices->clear();

    ui->connectionControl->setText(connectToDeviceStr);
    ui->connectionControl->setEnabled(false);
}

void BthCentralWidget::deviceWriteData(QBluetoothAddress address, QByteArray data){
    centralBackend->write(address, data);
}

