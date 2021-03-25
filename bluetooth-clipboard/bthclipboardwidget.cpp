#include "bthclipboardwidget.h"
#include "ui_bthclipboardwidget.h"

BthClipboardWidget::BthClipboardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BthClipboardWidget)
{
    ui->setupUi(this);

    //clipboardBackend =

    ui->copyToClipboard->setEnabled(false);
    ui->sendClipboard->setEnabled(false);

    connect(ui->sendClipboard, &QPushButton::clicked, this, [this](bool checked){
        auto currentClipboard = ui->receivedClipboards->currentItem();

        emit writeDeviceData(currentDevice, currentClipboard->text().toUtf8());
    });

    connect(ui->copyToClipboard, &QPushButton::clicked, this, [this](bool checked){
        auto currentClipboard = ui->receivedClipboards->currentItem();

        //clipboardBackend->copyToClipboard(currentClipboard->text());
    });

    connect(ui->clearList, &QPushButton::clicked, this, [this](bool checked){
        //clipboardBackend->clearCurrentClipboards();
        //auto deviceClipboard = clipboardBackend->getCurrentDeviceClipboard();
        //set UI

        ui->sendClipboard->setEnabled(false);
        ui->copyToClipboard->setEnabled(false);

        ui->receivedClipboards->clear();
    });

    connect(ui->receivedClipboards, &QListWidget::currentItemChanged, this, [this](QListWidgetItem *current, QListWidgetItem *previous){
        if(current != nullptr){
            ui->sendClipboard->setEnabled(true);
            ui->copyToClipboard->setEnabled(true);
        }
        else{
            ui->sendClipboard->setEnabled(false);
            ui->copyToClipboard->setEnabled(false);
        }
    });
}

BthClipboardWidget::~BthClipboardWidget()
{
    delete ui;
}

void BthClipboardWidget::onDeviceDataReceived(QBluetoothAddress address, QByteArray data){
    //clipboardBackend->addClipboard(address, data);
    //if(clipboardBackend->isCurrentDevice(address))
    //  auto deviceClipboard = clipboardBackend->getDeviceClipboard(address);
    //  set UI
}

void BthClipboardWidget::onDeviceChanged(QBluetoothAddress address){
    //  auto deviceClipboard = clipboardBackend->getDeviceClipboard(address);
    //  set UI
    //  currentDevice = address;
}

void BthClipboardWidget::onAbsentDevice(){
    ui->sendClipboard->setEnabled(false);
    ui->copyToClipboard->setEnabled(false);

    ui->receivedClipboards->clear();
}
