#include "bthclipboardwidget.h"
#include "ui_bthclipboardwidget.h"

BthClipboardWidget::BthClipboardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BthClipboardWidget)
{
    ui->setupUi(this);

    clipboardBackend = new BthClipboard(this);

    ui->copyToClipboard->setEnabled(false);
    ui->sendClipboard->setEnabled(false);

    connect(ui->sendClipboard, &QPushButton::clicked, this, [this](bool checked){
        auto currentClipboard = clipboardBackend->getClipboard();

        if(!currentClipboard.isEmpty())
            emit writeDeviceData(currentDevice, currentClipboard.toUtf8());
    });

    connect(ui->copyToClipboard, &QPushButton::clicked, this, [this](bool checked){
        auto currentClipboard = ui->receivedClipboards->currentItem();

        clipboardBackend->copyToClipboard(currentClipboard->text());
    });

    connect(ui->clearList, &QPushButton::clicked, this, [this](bool checked){
        clipboardBackend->clearClipboards(currentDevice);

        ui->copyToClipboard->setEnabled(false);

        ui->receivedClipboards->clear();
    });

    connect(ui->receivedClipboards, &QListWidget::currentItemChanged, this, [this](QListWidgetItem *current, QListWidgetItem *previous){
        if(current != nullptr){
            ui->copyToClipboard->setEnabled(true);
        }
        else{
            ui->copyToClipboard->setEnabled(false);
        }
    });
}

BthClipboardWidget::~BthClipboardWidget()
{
    delete clipboardBackend;
    delete ui;
}

void BthClipboardWidget::onDeviceDataReceived(const QString id, QByteArray data){
    clipboardBackend->addClipboard(id, data);

    ui->receivedClipboards->addItem(QString(data));
}

void BthClipboardWidget::onDeviceChanged(const QString id){
    auto deviceClipboards = clipboardBackend->getDeviceClipboards(id);

    ui->receivedClipboards->clear();
    ui->sendClipboard->setEnabled(true);

    for(auto i : deviceClipboards)
        ui->receivedClipboards->addItem(i);

    if(currentDevice != id)
        currentDevice = id;
}

void BthClipboardWidget::onAbsentDevice(){
    ui->sendClipboard->setEnabled(false);

    ui->receivedClipboards->clear();
}
